#include "queue.h"

uint8_t buff[2];
queue_t queue = {2, buff, buff};
queue_t *q = &queue;

void q_init(queue_t *q, uint8_t *buffer, size_t size)
{
	q->buff = buffer;
	q->head = buffer;
	q->tail = buffer;
	q->size = size;
}

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
	return q->size;
}
