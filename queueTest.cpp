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

TEST(queue, twoElementsSimultaneous)
{
	srand(TESTVALUE);
	uint8_t val[2];
	val[0] = rand() % 0xff;
	val[1] = rand() % 0xff;
	q_push(val[0]);
	q_push(val[1]);
	LONGS_EQUAL(val[0], q_pop());
	LONGS_EQUAL(val[1], q_pop());
}