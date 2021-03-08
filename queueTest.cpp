#include "CppUTest/TestHarness.h"

#include "queue.hpp"

#define TESTVALUE 0x55
#define RANDVALUE (rand() % 0xff)

TEST_GROUP(queue)
{
	void setup()
	{
		srand(TESTVALUE);
	}

	void teardown()
	{
	}

	void test_push_pop(uint8_t value)
	{
		q_push(value);
		LONGS_EQUAL(value, q_pop());
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
			LONGS_EQUAL(data[i], q_pop());
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