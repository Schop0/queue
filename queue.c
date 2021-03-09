#include "queue.h"

uint8_t buff[2];
queue_t queue = {2, buff, buff};
queue_t *q = &queue;

void q_push(uint8_t value)
{
	*(q->head)++ = value;
}

uint8_t q_pop(void)
{
	return *(q->tail)++;
}

size_t q_max(void)
{
	return q->length;
}
