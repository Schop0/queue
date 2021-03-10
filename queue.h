#include <stdint.h>
#include <stdbool.h>

typedef struct {
	size_t size;
	uint8_t *buff;
	uint8_t *head;
	uint8_t *tail;
} queue_t;

bool    q_init(queue_t *q, uint8_t *buffer, size_t size);
void    q_push(queue_t *q, uint8_t value);
uint8_t q_pop (queue_t *q);
size_t  q_max (queue_t *q);
