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
		q->head = q->data;
		q->tail = q->data;
		memset(q->data, TESTVALUE, q->length);
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
