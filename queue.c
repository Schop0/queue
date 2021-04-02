#include "queue.h"

#include <stddef.h>

/*
 * Private
 */

static inline
uint8_t * wraparound(const queue_t *q, uint8_t *ptr)
{
	if(ptr >= q->buff + q->size )
		ptr = q->buff;

	return ptr;
}

/*
 * Public
 */

bool q_init(queue_t *q, uint8_t *buffer, size_t size)
{
	if(!q || !buffer || !size)
		return false;

	q->buff  = buffer;
	q->head  = buffer;
	q->tail  = buffer;
	q->size  = size;
	q->empty = true;
	q->full  = false;

	return true;
}

bool q_push(queue_t *q, uint8_t value)
{
	if(!q || q->full)
		return false;

	*q->head = value;
	q->head  = wraparound(q, q->head+1);
	q->empty = false;
	q->full  = (q->tail == q->head);

	return true;
}

uint8_t q_pop(queue_t *q)
{
	if(!q || q->empty)
		return 0;

	uint8_t value = *q->tail;
	q->tail  = wraparound(q, q->tail+1);
	q->full  = false;
	q->empty = (q->tail == q->head);

	return value;
}

size_t q_size(queue_t *q)
{
	if(!q)
		return 0;

	return q->size;
}
