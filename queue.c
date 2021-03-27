#include "queue.h"

#include <stddef.h>

/*
 * Increment a pointer into a queue, wrapping as needed
 *
 * Arguments:
 *   - The queue associated with the pointer
 *   - A reference to the pointer to be incremented
 * Note: arguments are not checked. Ensure that:
 *   - The queue is valid
 *   - The pointer target is inside the queue's buffer
 */
static void increment_ptr(const queue_t *q, uint8_t **ptr)
{
	uint8_t *newPtr = ++(*ptr);

	if(newPtr >= (q->buff + q->size))
		newPtr = q->buff;

	*ptr = newPtr;
}

static bool isEmpty(const queue_t *q)
{
	return q->tail == NULL;
}

static bool isFull(const queue_t *q)
{
	return q->tail == q->head;
}

static void setEmpty(queue_t *q)
{
	q->tail = NULL;
}

bool q_init(queue_t *q, uint8_t *buffer, size_t size)
{
	if(!q || !buffer || !size)
		return false;

	q->buff = buffer;
	q->head = buffer;
	q->size = size;
	setEmpty(q);

	return true;
}

void q_push(queue_t *q, uint8_t value)
{
	if(!q)
		return;

	if(isFull(q))
		return;

	*q->head = value;

	if(isEmpty(q))
		q->tail = q->head;

	increment_ptr(q, &q->head);
}

uint8_t q_pop(queue_t *q)
{
	if(!q)
		return 0;

	if(isEmpty(q))
		return 0;

	uint8_t value = *q->tail;
	increment_ptr(q, &q->tail);

	if(q->tail == q->head)
		setEmpty(q);

	return value;
}

size_t q_max(queue_t *q)
{
	if(!q)
		return 0;

	return q->size;
}
