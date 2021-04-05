/** @file queue.c
 *
 * @par Copyright:
 * © 2021 Peter Buijs
 *
 * @par License:
 * SPDX-License-Identifier: MIT
 */
#include "queue.h"

#include <stddef.h>

/*!
 * Private prototypes
 */

static inline
uint8_t * wraparound(const queue_t *q, uint8_t *ptr);

/*!
 * Public
 */

bool q_init(queue_t *q, uint8_t *buffer, size_t size)
{
	if((NULL == q) || (NULL == buffer) || (0 == size))
	{
		return false;
	}

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
	if((NULL == q) || q->full)
	{
		return false;
	}

	// Push
	*q->head = value;
	q->head  = wraparound(q, q->head+1);
	q->empty = false;

	// When the head catches the tail, the queue is full
	if(q->tail == q->head)
	{
		q->full = true;
	}

	return true;
}

bool q_pop(queue_t *q, uint8_t *value)
{
	// Reject popping from a missing or empty queue
	if((NULL == q) || q->empty)
	{
		return false;
	}

	// Pop
	*value   = *q->tail;
	q->tail  = wraparound(q, q->tail+1);
	q->full  = false;

	// When the tail catches the head, the queue is empty
	if(q->tail == q->head)
	{
		q->empty = true;
	}

	return true;
}

size_t q_used(const queue_t *q)
{
	if(NULL == q)
	{
		return 0;
	}

	size_t used = 0;

	if(q->empty)
	{
		used = 0;
	}
	else
	if(q->full)
	{
		used = q->size;
	}
	else
	if(q->head > q->tail)
	{
		used = q->head - q->tail;
	}
	else
	{
		used = q->size - (q->tail - q->head);
	}

	return used;
}

size_t q_free(const queue_t *q)
{
	return q_size(q) - q_used(q);
}

/*!
 * Private
 */

static inline
uint8_t * wraparound(const queue_t *q, uint8_t *ptr)
{
	const uint8_t *out_of_bound = q->buff + q->size;

	while (out_of_bound <= ptr)
	{
		ptr -= q->size;
	}

	return ptr;
}

/*** end of file ***/
