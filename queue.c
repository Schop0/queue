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
	// Reject pushing to a missing or full queue
	if(!q || q->full)
		return false;

	// Push
	*q->head = value;
	q->head  = wraparound(q, q->head+1);
	q->empty = false;

	// When the head catches the tail, the queue is full
	if(q->tail == q->head)
		q->full = true;

	return true;
}

bool q_pop(queue_t *q, uint8_t *value)
{
	// Reject popping from a missing or empty queue
	if(!q || q->empty)
		return false;

	// Pop
	*value   = *q->tail;
	q->tail  = wraparound(q, q->tail+1);
	q->full  = false;

	// When the tail catches the head, the queue is empty
	if(q->tail == q->head)
		q->empty = true;

	return true;
}

size_t q_size(const queue_t *q)
{
	if(!q)
		return 0;

	return q->size;
}
