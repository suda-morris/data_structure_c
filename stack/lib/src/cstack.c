#include <stdlib.h>
#include "cstack.h"

typedef struct cstack_node {
    void *data_addr;
    struct list_head list;
} cstack_node_t;

static int stack_is_empty(cstack_t *stack)
{
    return list_is_empty(&stack->head);
}

static void stack_push(cstack_t *stack, void *data_addr)
{
    cstack_node_t *node = malloc(sizeof(cstack_node_t));
    node->data_addr = data_addr;
    list_add(&node->list, &stack->head);
}

static void *stack_top(cstack_t *stack)
{
    if (!stack_is_empty(stack)) {
        return list_entry(stack->head.next, cstack_node_t, list)->data_addr;
    } else {
        return NULL;
    }
}

static void *stack_pop(cstack_t *stack)
{
    cstack_node_t *node = NULL;
    void *ret = NULL;
    if (stack_is_empty(stack)) {
        return NULL;
    } else {
        node = list_entry(stack->head.next, cstack_node_t, list);
        ret = node->data_addr;
        list_del_init(stack->head.next);
        free(node);
        return ret;
    }
}

cstack_t *newCStack(void)
{
    cstack_t *stack = malloc(sizeof(cstack_t));
    INIT_LIST_HEAD(&stack->head);
    stack->is_empty = stack_is_empty;
    stack->pop = stack_pop;
    stack->top = stack_top;
    stack->push = stack_push;
    return stack;
}

void freeCStack(cstack_t *stack)
{
    while (!stack_is_empty(stack)) {
        stack_pop(stack);
    }
    free(stack);
    stack = NULL;
}
