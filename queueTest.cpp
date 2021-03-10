#include "CppUTest/TestHarness.h"

#include "queue.hpp"
#include <cstring>
#include <iostream>

#define TESTSIZE_SMALL 2
#define TESTSIZE_LARGE 1025
#define TESTVALUE 0x55
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

TEST(queue, singleElement)
{
	CHECK(q_init(&queue, buffer, sizeof buffer));
	test_push_pop(TESTVALUE);
}

TEST(queue, twoElementsSequential)
{
	CHECK(q_init(&queue, buffer, sizeof buffer));
	test_push_pop(RANDVALUE);
	test_push_pop(RANDVALUE);
}

TEST(queue, twoElementsSimultaneous)
{
	CHECK(q_init(&queue, buffer, sizeof buffer));
	test_push_pop_random_data(2);
}

TEST(queue, maxElementsSimultaneous)
{
	CHECK(q_init(&queue, buffer, sizeof buffer));
	test_push_pop_random_data(q_max(&queue));
}

TEST(queue, initQueue)
{
	CHECK(q_init(&queue, buffer, sizeof buffer));
	UNSIGNED_LONGS_EQUAL(sizeof buffer, queue.size);
	POINTERS_EQUAL(buffer, queue.buff);
	POINTERS_EQUAL(buffer, queue.head);
	POINTERS_EQUAL(buffer, queue.tail);
}

TEST(queue, initNull)
{
	CHECK_FALSE(q_init(NULL, buffer, sizeof buffer));
}

TEST(queue, pushToNull)
{
	q_push(NULL, RANDVALUE);
}

TEST(queue, popFromNull)
{
	q_pop(NULL);
}

TEST(queue, maxSizeOfNull)
{
	q_max(NULL);
}

TEST(queue, initNullData)
{
	CHECK_FALSE(q_init(&queue, NULL, sizeof buffer));
}

TEST(queue, initZeroSize)
{
	CHECK_FALSE(q_init(&queue, buffer, 0));
}

TEST(queue, maxSize)
{
	CHECK(q_init(&queue, buffer, sizeof buffer));
	UNSIGNED_LONGS_EQUAL(sizeof buffer, q_max(&queue));

	CHECK(q_init(&queue, bigbuf, sizeof bigbuf));
	UNSIGNED_LONGS_EQUAL(sizeof bigbuf, q_max(&queue));
}
