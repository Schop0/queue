#include "queue.h"

static uint8_t data;

void q_push(uint8_t value)
{
	data = value;
}

uint8_t q_pop(void)
{
	return data;
}
