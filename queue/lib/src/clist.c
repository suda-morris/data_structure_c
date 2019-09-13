#include "clist.h"

/**
 * 初始化表头节点
 */
inline void INIT_LIST_HEAD(struct list_head *head)
{
    head->next = head;
    head->prev = head;
}

/**
 * 把node插入到prev和next之间
 */
inline void __add(struct list_head *node, struct list_head *prev,
                  struct list_head *next)
{
    prev->next = node;
    next->prev = node;
    node->prev = prev;
    node->next = next;
}

/**
 * 删除指定节点
 */
inline void list_del_init(struct list_head *node)
{
    node->prev->next = node->next;
    node->next->prev = node->prev;
    INIT_LIST_HEAD(node);
}

/**
 * 插入节点到head的后面，【栈】
 */
inline void list_add(struct list_head *node, struct list_head *head)
{
    __add(node, head, head->next);
}

/**
 * 插入节点到head的前面，【队列】
 */
inline void list_add_tail(struct list_head *node, struct list_head *head)
{
    __add(node, head->prev, head);
}

/**
 * 判断链表是否为空
 */
inline int list_is_empty(struct list_head *head)
{
    return head->next == head;
}
