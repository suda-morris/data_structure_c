#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "clist.h"

typedef struct cstack cstack_t;
struct cstack {
    struct list_head head;
    void *(*top)(cstack_t *stack);
    int (*is_empty)(cstack_t *stack);
    void *(*pop)(cstack_t *stack);
    void (*push)(cstack_t *stack, void *data_addr);
};

cstack_t *newCStack(void);
void freeCStack(cstack_t *stack);

#ifdef __cplusplus
}
#endif
