#pragma once
#ifdef __cplusplus
extern "C" {
#endif
/**
 * 描述链表上的表头节点
 */
struct list_head {
    struct list_head *prev;
    struct list_head *next;
};

#define LIST_HEAD(name)\
        struct list_head name = {&(name),&(name)}

#ifndef offsetof
#define offsetof(type,member)\
        ((size_t)(&((type*)0)->member))
#endif

#ifndef container_of
#define container_of(ptr,type,member)\
        ((type*)((size_t)(ptr)-offsetof(type,member)))
#endif

#define list_entry(ptr,type,member)\
        container_of(ptr,type,member)

/**
 * 内核链表的普通遍历(遍历的过程中不能删除节点)
 */
#define list_for_each(cur,head)\
        for(cur=(head)->next;\
        cur!=(head);\
        cur=(cur)->next)

/**
 * 内核链表的安全遍历(遍历的同时可以删除节点)
 */
#define list_for_each_safe(cur,tmp,head)\
        for(cur=(head)->next,tmp=(cur)->next;\
        cur!=(head);\
        cur=(tmp),tmp=(cur)->next)

/**
 * 自定义链表的普通遍历(遍历过程中不能删除节点)
 */
#define list_for_each_entry(ptr,head,member)\
        for(ptr=list_entry((head)->next,typeof(*(ptr)),member);\
        &(ptr)->member!=(head);\
        ptr=list_entry((ptr)->member.next,typeof(*(ptr)),member))

/**
 * 自定义链表的安全遍历(遍历的同时可以删除节点)
 */
#define list_for_each_entry_safe(ptr,tmp,head,member)\
        for(ptr=list_entry((head)->next,typeof(*(ptr)),member),tmp=list_entry((ptr)->member.next,typeof(*(tmp)),member);\
        &(ptr)->member!=(head);\
        ptr=(tmp),tmp=list_entry((tmp)->member.next,typeof(*(tmp)),member))


void INIT_LIST_HEAD(struct list_head *head);
void __add(struct list_head *node, struct list_head *prev,
           struct list_head *next);
void list_del_init(struct list_head *node);
void list_add(struct list_head *node, struct list_head *head);
void list_add_tail(struct list_head *node, struct list_head *head);
int list_is_empty(struct list_head *head);

#ifdef __cplusplus
}
#endif
