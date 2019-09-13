#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "clist.h"

typedef struct cqueue cqueue_t;
struct cqueue {
    struct list_head head;
    void *(*top)(cqueue_t *queue);
    int (*is_empty)(cqueue_t *queue);
    void *(*pop)(cqueue_t *queue);
    void (*push)(cqueue_t *queue, void *data_addr);
};

cqueue_t *newCQueue(void);
void freeCQueue(cqueue_t *queue);

#ifdef __cplusplus
}
#endif
