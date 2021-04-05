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
