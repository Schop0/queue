#include "queue.h"

bool q_init(queue_t *q, uint8_t *buffer, size_t size)
{
	if(!q || !buffer || !size)
		return false;

	q->buff = buffer;
	q->head = buffer;
	q->tail = buffer;
	q->size = size;

	return true;
}

void q_push(queue_t *q, uint8_t value)
{
	if(!q)
		return;

	if(q->head >= (q->buff + q->size))
		q->head = q->buff;

	*(q->head)++ = value;
}

uint8_t q_pop(queue_t *q)
{
	if(!q)
		return 0;

	if(q->tail >= (q->buff + q->size))
		q->tail = q->buff;

	return *(q->tail)++;
}

size_t q_max(queue_t *q)
{
	if(!q)
		return 0;

	return q->size;
}
