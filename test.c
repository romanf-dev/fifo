/*
 * Basic tests for singly-linked intrusive FIFO queue.
 */

#include <stdio.h>
#include <assert.h>
#include "fifo.h"

struct test_node {
    int n;
    struct node_t link;
};

#define N 5

#if N < 2
#error N must be at least 2
#endif

struct fifo_t queue;
struct test_node item[N];

int main(void) {
    fifo_init(&queue);
    assert(fifo_empty(&queue));

    for (int i = 0; i < N; ++i) {
        item[i].n = i;
        fifo_enqueue(&queue, &(item[i].link));
    }
    
    printf("inserted %d sequential items\r\n", N);

    for (int i = 0; i < N; ++i) {
        assert(fifo_empty(&queue) == false);
        struct node_t* ptr = fifo_dequeue(&queue);
        struct test_node* node = fifo_entry(ptr, struct test_node, link);
        assert(node == &item[i]);
        assert(node->n == i);
        printf("dequeued item: %d\r\n", node->n);
    }

    assert(fifo_empty(&queue));
    
    for (int i = 0; i < N; ++i) {
        item[i].n = i * 2;
        fifo_enqueue(&queue, &(item[i].link));
    }
    
    printf("inserted %d even items\r\n", N);

    while (!fifo_empty(&queue)) {
        struct node_t* ptr = fifo_dequeue(&queue);
        struct test_node* node = fifo_entry(ptr, struct test_node, link);
        printf("dequeued item: %d\r\n", node->n);
    }

    assert(fifo_empty(&queue));

    for (int i = 0; i < N; ++i) {
        item[i].n = i;
        fifo_enqueue(&queue, &(item[i].link));
    }
    
    printf("inserted %d sequential items\r\npop/push 2 first items\r\n", N);

    (void) fifo_dequeue(&queue); /* remove item[0] */
    (void) fifo_dequeue(&queue); /* remove item[1] */
    fifo_enqueue(&queue, &(item[0].link)); /* re-insert item[0] */
    fifo_enqueue(&queue, &(item[1].link)); /* re-insert item[1] */

    while (!fifo_empty(&queue)) {
        struct node_t* ptr = fifo_dequeue(&queue);
        struct test_node* node = fifo_entry(ptr, struct test_node, link);
        printf("dequeued item: %d\r\n", node->n);
    }

    assert(fifo_empty(&queue));
    return 0;
}

