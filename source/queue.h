/** @file queue.h
 *
 * @brief Queue that stores bytes in first-in first-out order
 *
 * This queue is suitable for static alocation and is reentrant, because of
 * caller-provided storage. It may be used in the context of interrupt handlers.
 *
 * For the sake of simplicity, the implementation of queue_t is visible, but
 * it MUST NOT be manipulated directly. Doing so is undefined behavior.
 *
 * @par Copyright:
 * © 2021 Peter Buijs
 *
 * @par License:
 * SPDX-License-Identifier: MIT
 */
#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
	size_t size;
	uint8_t *buff;
	uint8_t *head;
	uint8_t *tail;
	bool empty;
	bool full;
} queue_t;

bool    q_init(queue_t *q, uint8_t *buffer, size_t size);
bool    q_push(queue_t *q, uint8_t value);
bool    q_pop (queue_t *q, uint8_t *value);
size_t  q_used(const queue_t *q);
size_t  q_free(const queue_t *q);
inline bool   q_empty(const queue_t *q) { return NULL == q ? 0 : q->empty; }
inline bool   q_full (const queue_t *q) { return NULL == q ? 0 : q->full ; }
inline size_t q_size (const queue_t *q) { return NULL == q ? 0 : q->size ; }

#endif /* QUEUE_H */

/*** end of file ***/
