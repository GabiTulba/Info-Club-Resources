#ifndef LINKED_LIST
#define LINKED_LIST

#include <stdlib.h>
#include <string.h>

typedef struct _Node {
    void *data;
    size_t data_size;
    struct _Node *next, *prev;
} Node;

typedef struct _LinkedList {
    Node *head, *tail;
    size_t size;
}LinkedList;

// initialize
LinkedList *list_init();

// capacity
size_t list_get_size(LinkedList *list);
int list_is_empty(LinkedList *list);

// element access
Node *list_front(LinkedList *list);
Node *list_back(LinkedList *list);
Node *list_access(LinkedList *list, size_t pos);

// modifiers
void list_push_front(LinkedList *list, void *new_data, size_t data_size);
void list_pop_front(LinkedList *list);
void list_push_back(LinkedList *list, void *new_data, size_t data_size);
void list_pop_back(LinkedList *list);
Node *list_insert(LinkedList *list, size_t pos, void *new_data, size_t data_size);
Node *list_erase(LinkedList *list, size_t pos);
void list_swap(LinkedList *list1, LinkedList *list2);
void list_resize(LinkedList *list, size_t new_size, size_t data_size);
void list_clear(LinkedList *list);
void list_free(LinkedList *list);
/*
// operations
void list_splice(Node *position, LinkedList *list, Node *first, Node *last);
void list_remove(LinkedList *list, void *data, size_t data_size);
void list_remove_if(LinkedList, int (*comp)(void *));
void list_unique(LinkedList *list);
void list_merge(LinkedList *list, int (*comp)(void *, void *));
void list_sort(LinkedList *list, int (*comp)(void *, void *));
void list_reverse(LinkedList *list);
*/
#endif /*LINKED_LIST*/
