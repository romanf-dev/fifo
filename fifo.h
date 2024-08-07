/*
 * Singly-linked intrusive FIFO queue with constant time for all operations
 * This implementation does not use conditionals.
 */

#ifndef FIFO_H
#define FIFO_H

#include <stddef.h>
#include <stdbool.h>

struct node_t {
    struct node_t* next;
};

struct fifo_t {
    struct node_t dummy;
    struct node_t* tail;
};

#define fifo_entry(p, type, member) ((type*)((char*)(p) - offsetof(type, member)))

static inline void fifo_init(struct fifo_t* fifo) {
    fifo->tail = &fifo->dummy;
    fifo->dummy.next = 0;
}

static inline bool fifo_empty(struct fifo_t* fifo) {
    return fifo->tail == &fifo->dummy;
}

static inline void fifo_enqueue(struct fifo_t* fifo, struct node_t* node) {
    node->next = node;
    fifo->tail->next = node;
    fifo->tail = node;
}

static inline struct node_t* fifo_dequeue(struct fifo_t* fifo) {
    struct node_t* const node = fifo->dummy.next;
    fifo->dummy.next = node->next;
    node->next = &fifo->dummy;
    fifo->tail = fifo->tail->next;
    return node;
}

#endif

