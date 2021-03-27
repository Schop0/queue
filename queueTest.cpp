#include "CppUTest/TestHarness.h"

#include "queue.hpp"
#include <cstring>
#include <iostream>

#define TESTSIZE_SMALL 5
#define TESTSIZE_LARGE 1025
#define TESTVALUE 0x55
#define MARKVALUE 0xAA
#define RANDVALUE (rand() % 0xff)

TEST_GROUP(queue)
{
	uint8_t buffer[TESTSIZE_SMALL];
	uint8_t bigbuf[TESTSIZE_LARGE]; // Not initialised
	queue_t queue;

	void setup()
	{
		memset(buffer, TESTVALUE, sizeof buffer);
		memset(&queue, TESTVALUE, sizeof queue );
		srand(TESTVALUE);
	}

	void teardown()
	{
	}

	void test_push_pop(uint8_t value)
	{
		q_push(&queue, value);
		BYTES_EQUAL(value, q_pop(&queue));
	}

	void test_push_pop_random_data(size_t length)
	{
		uint8_t data[length];
		unsigned int i;

		for(i=0; i<length; i++) {
			data[i] = RANDVALUE;
			q_push(&queue, data[i]);
		}

		for(i=0; i<length; i++)
			BYTES_EQUAL(data[i], q_pop(&queue));
	}
};

// Store and retrieve one value
TEST(queue, singleElement)
{
	CHECK(q_init(&queue, buffer, sizeof buffer));
	test_push_pop(TESTVALUE);
}

// Store and retrieve multiple values one at a time
TEST(queue, twoElementsSequential)
{
	CHECK(q_init(&queue, buffer, sizeof buffer));
	test_push_pop(RANDVALUE);
	test_push_pop(RANDVALUE);
}

// Store and retrieve multiple values simultaneously in fifo order
TEST(queue, twoElementsSimultaneous)
{
	CHECK(q_init(&queue, buffer, sizeof buffer));
	test_push_pop_random_data(2);
}

// Store and retrieve the maximum number of elements
TEST(queue, maxElementsSimultaneous)
{
	CHECK(q_init(&queue, buffer, sizeof buffer));
	test_push_pop_random_data(q_max(&queue));
}

// Internal workings, should not be tested
TEST(queue, initQueue)
{
	CHECK(q_init(&queue, buffer, sizeof buffer));
	UNSIGNED_LONGS_EQUAL(sizeof buffer, queue.size);
	POINTERS_EQUAL(buffer, queue.buff);
	POINTERS_EQUAL(buffer, queue.head);
	POINTERS_EQUAL(buffer, queue.tail);
}

// Do not dereference null pointer
TEST(queue, initNull)
{
	CHECK_FALSE(q_init(NULL, buffer, sizeof buffer));
}

// Do not dereference null pointer
TEST(queue, pushToNull)
{
	q_push(NULL, RANDVALUE);
}

// Do not dereference null pointer
TEST(queue, popFromNull)
{
	q_pop(NULL);
}

// Do not dereference null pointer
TEST(queue, maxSizeOfNull)
{
	q_max(NULL);
}

// Refuse to intialise without a buffer
TEST(queue, initNullData)
{
	CHECK_FALSE(q_init(&queue, NULL, sizeof buffer));
}

// Refuse to intialise with a zero size buffer
TEST(queue, initZeroSize)
{
	CHECK_FALSE(q_init(&queue, buffer, 0));
}

// Maximum number of elements matches storage size
TEST(queue, maxSize)
{
	CHECK(q_init(&queue, buffer, sizeof buffer));
	UNSIGNED_LONGS_EQUAL(sizeof buffer, q_max(&queue));

	CHECK(q_init(&queue, bigbuf, sizeof bigbuf));
	UNSIGNED_LONGS_EQUAL(sizeof bigbuf, q_max(&queue));
}

// Store and retrieve more than the maximum elements, in smaller batches
TEST(queue, maxElementsMultipleTimes)
{
	CHECK(q_init(&queue, buffer, sizeof buffer));
	test_push_pop_random_data(q_max(&queue));
	test_push_pop_random_data(q_max(&queue));
}

// Do not write outside the storage bounds
TEST(queue, boundsProtection)
{
	size_t usable_size = (sizeof buffer) - 2;
	buffer[0] = MARKVALUE;
	buffer[usable_size+1] = MARKVALUE;

	CHECK(q_init(&queue, &buffer[1], usable_size));

	size_t q_size = q_max(&queue);
	UNSIGNED_LONGS_EQUAL(usable_size, q_size);

	unsigned int overflow = 1;
	for(unsigned int i = 0; i < q_size+overflow; i++)
		q_push(&queue, TESTVALUE);

	BYTES_EQUAL(MARKVALUE, buffer[0]);
	BYTES_EQUAL(MARKVALUE, buffer[usable_size+1]);
}

// Do not clobber elements when full, reject more
// Accept all possible binary values for data
// (how?) multiple independent instances
// (every method) Do not dereference null pointers
// (every method) Do not dereference pointers outside the storage area
// (every method) Do not change storage location and size
