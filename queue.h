#include <stdint.h>

typedef struct {
	size_t length;
	uint8_t *data;
	uint8_t *head;
	uint8_t *tail;
} queue_t;

extern queue_t *q;

void q_push(uint8_t value);
uint8_t q_pop(void);
size_t q_max(void);
