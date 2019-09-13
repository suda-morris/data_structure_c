#include <stdlib.h>
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

/**
 * 初始化表头结点
 */
inline void INIT_HLIST_HEAD(struct hlist_head *head)
{
    head->first = NULL;
}

/**
 * 初始化节点
 */
inline void INIT_HLIST_NODE(struct hlist_node *node)
{
    node->next = NULL;
    node->pprev = &node;
}

/**
 * 判断是否是空
 */
inline int hlist_is_empty(const struct hlist_head *head)
{
    return !head->first;
}

/**
 * 将node插入到head后面
 */
inline void hlist_add_head(struct hlist_node *node, struct hlist_head *head)
{
    struct hlist_node *first = head->first;
    node->next = first;
    if (first) {
        first->pprev = &node->next;
    }
    head->first = node;
    node->pprev = &head->first;
}

/**
 * 将node插入到base节点的前面
 */
inline void hlist_add_before(struct hlist_node *node, struct hlist_node *base)
{
    node->pprev = base->pprev;
    node->next = base;
    base->pprev = &node->next;
    *(node->pprev) = node;
}

/**
 * 将node插入到base节点的后面
 */
inline void hlist_add_behind(struct hlist_node *node, struct hlist_node *base)
{
    node->next = base->next;
    base->next = node;
    node->pprev = &base->next;

    if (node->next) {
        node->next->pprev = &node->next;
    }
}

/**
 * hlist中删除节点
 */
inline void hlist_del_init(struct hlist_node *node)
{
    struct hlist_node *next = node->next;
    struct hlist_node **pprev = node->pprev;

    *pprev = next;
    if (next) {
        next->pprev = pprev;
    }

    INIT_HLIST_NODE(node);
}
