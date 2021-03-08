#include "CppUTest/TestHarness.h"

#include "queue.hpp"

#define TESTVALUE 0x55

TEST_GROUP(queue)
{
	void setup()
	{
	}

	void teardown()
	{
	}

	void test_push_pop(uint8_t value)
	{
		q_push(value);
		LONGS_EQUAL(value, q_pop());
	}
};

TEST(queue, singleElement)
{
	test_push_pop(TESTVALUE);
}

TEST(queue, twoElementsSequential)
{
	srand(TESTVALUE);
	test_push_pop(rand() % 0xff);
	test_push_pop(rand() % 0xff);
}
