#include "CppUTest/TestHarness.h"

#include "queue.hpp"
#include <cstring>

#define TESTVALUE 0x55
#define RANDVALUE (rand() % 0xff)

TEST_GROUP(queue)
{
	void setup()
	{
		srand(TESTVALUE);
		q->head = q->buff;
		q->tail = q->buff;
		memset(q->buff, TESTVALUE, q->size);
	}

	void teardown()
	{
	}

	void test_push_pop(uint8_t value)
	{
		q_push(value);
		BYTES_EQUAL(value, q_pop());
	}

	void test_push_pop_random_data(size_t length)
	{
		uint8_t data[length];
		unsigned int i;

		for(i=0; i<length; i++) {
			data[i] = RANDVALUE;
			q_push(data[i]);
		}

		for(i=0; i<length; i++)
			BYTES_EQUAL(data[i], q_pop());
	}
};

TEST(queue, singleElement)
{
	test_push_pop(TESTVALUE);
}

TEST(queue, twoElementsSequential)
{
	test_push_pop(RANDVALUE);
	test_push_pop(RANDVALUE);
}

TEST(queue, twoElementsSimultaneous)
{
	test_push_pop_random_data(2);
}

TEST(queue, maxElementsSimultaneous)
{
	test_push_pop_random_data(q_max());
}

TEST(queue, initQueue)
{
	uint8_t buffer[2] = {0};
	queue_t queue = {0};

	CHECK(q_init(&queue, buffer, sizeof buffer));

	UNSIGNED_LONGS_EQUAL(sizeof buffer, queue.size);
	POINTERS_EQUAL(buffer, queue.buff);
	POINTERS_EQUAL(buffer, queue.head);
	POINTERS_EQUAL(buffer, queue.tail);
}

TEST(queue, initVoidQueue)
{
	uint8_t buffer[2] = {0};

	CHECK_FALSE(q_init(NULL, buffer, sizeof buffer));
}

TEST(queue, initVoidData)
{
	queue_t queue = {0};

	CHECK_FALSE(q_init(&queue, NULL, 2));
}

TEST(queue, initZeroSize)
{
	uint8_t buffer[2] = {0};
	queue_t queue = {0};

	CHECK_FALSE(q_init(&queue, buffer, 0));
}
