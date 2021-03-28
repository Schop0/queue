#include "CppUTest/TestHarness.h"

#include "queue.hpp"
#include <cstring>
#include <iostream>

#define TESTSIZE_SMALL 5
#define TESTSIZE_LARGE 1025
#define TESTVALUE 0x55
#define MARKVALUE 0xAA
#define RANDVALUE (rand() % 0xff)

static uint8_t buffer[TESTSIZE_SMALL];
static uint8_t bigbuf[TESTSIZE_LARGE];
static queue_t queue;

static void common_setup()
{
	memset(buffer, MARKVALUE, sizeof buffer);
	memset(bigbuf, MARKVALUE, sizeof buffer);
	memset(&queue, MARKVALUE, sizeof queue );
	srand(TESTVALUE);
}

static  void test_push_pop(uint8_t value)
{
	q_push(&queue, value);
	BYTES_EQUAL(value, q_pop(&queue));
}

static  void test_push_pop_random_data(size_t push_length, unsigned int ignore_end)
{
	uint8_t data[push_length];
	size_t pop_length = push_length - ignore_end;
	unsigned int i;

	for(i=0; i<push_length; i++) {
		data[i] = RANDVALUE;
		q_push(&queue, data[i]);
	}

	for(i=0; i<pop_length; i++)
		BYTES_EQUAL(data[i], q_pop(&queue));
}

TEST_GROUP(queue)
{
	void setup()
	{
		common_setup();
		CHECK(q_init(&queue, buffer, sizeof buffer));
	}
};

TEST_GROUP(queue_noInit)
{
	void setup()
	{
		common_setup();
	}
};

// Store and retrieve one value
TEST(queue, singleElement)
{
	test_push_pop(TESTVALUE);
}

// Store and retrieve multiple values one at a time
TEST(queue, twoElementsSequential)
{
	test_push_pop(RANDVALUE);
	test_push_pop(RANDVALUE);
}

// Store and retrieve multiple values simultaneously in fifo order
TEST(queue, twoElementsSimultaneous)
{
	test_push_pop_random_data(2, 0);
}

// Store and retrieve the maximum number of elements
TEST(queue, maxElementsSimultaneous)
{
	test_push_pop_random_data(q_size(&queue), 0);
}

// Do not dereference null pointer
TEST(queue_noInit, initNull)
{
	CHECK_FALSE(q_init(NULL, buffer, sizeof buffer));
	q_push(NULL, RANDVALUE);
	q_pop(NULL);
	q_size(NULL);
}

// Refuse to intialise without a buffer
TEST(queue_noInit, initNullData)
{
	CHECK_FALSE(q_init(&queue, NULL, sizeof buffer));
	CHECK_FALSE(q_init(&queue, buffer, 0));
}

// Maximum number of elements matches storage size
TEST(queue, maxSize)
{
	UNSIGNED_LONGS_EQUAL(sizeof buffer, q_size(&queue));

	CHECK(q_init(&queue, bigbuf, sizeof bigbuf));
	UNSIGNED_LONGS_EQUAL(sizeof bigbuf, q_size(&queue));
}

// Store and retrieve more than the maximum elements, in smaller batches
TEST(queue, maxElementsMultipleTimes)
{
	test_push_pop_random_data(q_size(&queue), 0);
	test_push_pop_random_data(q_size(&queue), 0);
}

// Do not write outside the storage bounds
// Do not clobber elements when full, reject more
TEST(queue_noInit, boundsProtection)
{
	size_t usable_size = (sizeof buffer) - 2;
	buffer[0] = MARKVALUE;
	buffer[usable_size+1] = MARKVALUE;

	CHECK(q_init(&queue, &buffer[1], usable_size));

	unsigned int overflow = 1;
	test_push_pop_random_data(usable_size+overflow, overflow);

	BYTES_EQUAL(MARKVALUE, buffer[0]);
	BYTES_EQUAL(MARKVALUE, buffer[usable_size+1]);
}

// Reject popping from an empty queue
TEST(queue, pushAfterPopFromEmpty)
{
	q_pop(&queue);
	test_push_pop(RANDVALUE);

	q_pop(&queue);
	test_push_pop_random_data(q_size(&queue), 0);
}

// Accept all possible binary values for data
TEST(queue, acceptAnyValue)
{
	for(unsigned int i=0; i<=UINT8_MAX; i++)
		test_push_pop((uint8_t)i);
}

// Let caller detect a failed push
// Let caller detect a failed pop
// Provide a way to determine free space
// Provide a way to determine used space
// (how?) multiple independent instances
// (every method) Do not dereference null pointers
// (every method) Do not dereference pointers outside the storage area
// (every method) Do not change storage location and size
