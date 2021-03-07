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
