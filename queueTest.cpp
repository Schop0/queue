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
};

TEST(queue, singleElement)
{
	q_push(TESTVALUE);
	LONGS_EQUAL(TESTVALUE, q_pop());
}

TEST(queue, twoElements)
{
	uint8_t testvalue;
	srand(TESTVALUE);

	testvalue = rand() % 0xff;
	q_push(testvalue);
	LONGS_EQUAL_TEXT(testvalue, q_pop(), "First");

	testvalue = rand() % 0xff;
	q_push(testvalue);
	LONGS_EQUAL_TEXT(testvalue, q_pop(), "Second");
}
