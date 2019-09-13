#include <assert.h>
#include <stdlib.h>
#include "cqueue.h"

typedef struct cqueue_node {
    void *data_addr;
    struct list_head list;
} cqueue_node_t;

static int queue_is_empty(cqueue_t *queue)
{
    return list_is_empty(&queue->head);
}

static void queue_push(cqueue_t *queue, void *data_addr)
{
    cqueue_node_t *node = malloc(sizeof(cqueue_node_t));
    assert(node);
    node->data_addr = data_addr;
    list_add_tail(&node->list, &queue->head);
}

static void *queue_top(cqueue_t *queue)
{
    if (!queue_is_empty(queue)) {
        return list_entry(queue->head.next, cqueue_node_t, list)->data_addr;
    } else {
        return NULL;
    }
}

static void *queue_pop(cqueue_t *queue)
{
    cqueue_node_t *node = NULL;
    void *ret = NULL;
    if (queue_is_empty(queue)) {
        return NULL;
    } else {
        node = list_entry(queue->head.next, cqueue_node_t, list);
        ret = node->data_addr;
        list_del_init(queue->head.next);
        free(node);
        return ret;
    }
}

cqueue_t *newCQueue(void)
{
    cqueue_t *queue = malloc(sizeof(cqueue_t));
    assert(queue);
    INIT_LIST_HEAD(&queue->head);
    queue->is_empty = queue_is_empty;
    queue->pop = queue_pop;
    queue->top = queue_top;
    queue->push = queue_push;
    return queue;
}

void freeCQueue(cqueue_t *queue)
{
    while (!queue_is_empty(queue)) {
        queue_pop(queue);
    }
    free(queue);
    queue = NULL;
}
