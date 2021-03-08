#include "queue.h"

static uint8_t data[2];
static uint8_t *head = &data[0];
static uint8_t *tail = &data[0];

void q_push(uint8_t value)
{
	*head++ = value;
}

uint8_t q_pop(void)
{
	return *tail++;
}

size_t q_max(void)
{
	return sizeof data;
}
