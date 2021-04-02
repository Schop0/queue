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
uint8_t q_pop (queue_t *q);
bool q_pop_checked(queue_t *q, uint8_t *value);
size_t  q_size(queue_t *q);
