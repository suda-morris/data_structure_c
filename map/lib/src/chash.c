#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chash.h"

/**
 * 描述插入到hash链表中的节点
 */
struct hash_node {
    char key[CHASH_KEY_LEN];
    char value[CHASH_VALUE_LEN];
    struct hlist_node list_node;
};

static size_t hash_alog(struct hash_list *list, const char *key)
{
    size_t sum = 0;
    char *p = (char *) key;
    while (*p) {
        sum += *p++;
    }
    return sum % list->arr_len;
}

static void hash_insert(struct hash_list *list, const char *key,
                        const char *value)
{
    size_t hash_value = hash_alog(list, key);
    struct hash_node *ptr = NULL;
    hlist_for_each_entry(ptr, list->parr + hash_value, list_node) {
        if (!strcmp(ptr->key, key)) {
            if (strcmp(ptr->value, value)) {
                memset(ptr->value, 0, CHASH_VALUE_LEN);
                strcpy(ptr->value, value);
            }
            return;
        }
    }

    ptr = malloc(sizeof(struct hash_node));
    assert(ptr);
    strcpy(ptr->key, key);
    strcpy(ptr->value, value);
    INIT_HLIST_NODE(&ptr->list_node);

    hlist_add_head(&ptr->list_node, list->parr + hash_value);
}

static char *hash_search(struct hash_list *list, const char *key)
{
    size_t hash_value = hash_alog(list, key);
    struct hash_node *ptr = NULL;
    hlist_for_each_entry(ptr, list->parr + hash_value, list_node) {
        if (!strcmp(ptr->key, key)) {
            return ptr->value;
        }
    }
    return NULL;
}

static void hash_del(struct hash_list *list, const char *key)
{
    size_t hash_value = hash_alog(list, key);
    struct hash_node *ptr = NULL;
    struct hash_node *tmp = NULL;
    hlist_for_each_entry_safe(ptr, tmp, list->parr + hash_value, list_node) {
        if (!strcmp(ptr->key, key)) {
            hlist_del_init(&ptr->list_node);
            free(ptr);
        }
    }
}

static void hash_print(struct hash_list *list)
{
    struct hash_node *ptr = NULL;
    struct hlist_node *cur = NULL;
    for (int i = 0; i < list->arr_len; i++) {
        printf("第%d条链表：", i + 1);
        hlist_for_each(cur, list->parr + i) {
            ptr = hlist_entry(cur, typeof(*ptr), list_node);
            printf(" --> [%s:%s] ", ptr->key, ptr->value);
        }
        printf("\r\n");
    }
}

struct hash_list *newHashList(size_t len)
{
    struct hash_list *list = NULL;
    list = malloc(sizeof(struct hash_list) + sizeof(struct hlist_head) * len);
    assert(list);
    list->arr_len = len;
    for (size_t i = 0; i < len; i++) {
        INIT_HLIST_HEAD(list->parr + i);
    }

    list->alog = hash_alog;
    list->insert = hash_insert;
    list->print = hash_print;
    list->search = hash_search;
    list->del = hash_del;
    return list;
}

void freeHashList(struct hash_list *list)
{
    struct hash_node *ptr = NULL;
    struct hlist_node *cur = NULL;
    struct hlist_node *tmp = NULL;
    for (int i = 0; i < list->arr_len; i++) {
        hlist_for_each_safe(cur, tmp, list->parr + i) {
            hlist_del_init(cur);
            ptr = hlist_entry(cur, typeof(*ptr), list_node);
            free(ptr);
        }
    }
    free(list);
    list = NULL;
}
