#include "LinkedList.h"

void node_swap(Node **a, Node **b) {
    Node *aux = *a;
    *a = *b;
    *b = aux;
}

void size_t_swap(size_t *a, size_t *b) {
    size_t aux = *a;
    *a = *b;
    *b = aux;
}

void void_swap(void **a, void **b) {
    void *aux = *a;
    *a = *b;
    *b = aux;
}

LinkedList *list_init() {
    LinkedList *list = (LinkedList *) malloc(sizeof(LinkedList));

    list->head = list->tail = NULL;
    list->size = 0;

    return list;
}

Node *make_node(void *new_data, size_t data_size) {
    Node *new_node = (Node *) malloc(sizeof(Node));

    new_node->data = malloc(data_size);
    new_node->data_size = data_size;
    memcpy(new_node->data, new_data, data_size);

    return new_node;
}

size_t list_get_size(LinkedList *list) {
    return list->size;
}

int list_is_empty(LinkedList *list) {
    return list->size == 0;
}

Node *list_front(LinkedList *list) {
    return list->head;
}

Node *list_back(LinkedList *list) {
    return list->tail;
}

Node *list_access(LinkedList *list, size_t pos) {
    if(pos >= list->size)
        return NULL;

    Node *it;

    if(pos < list->size / 2) {
        it = list->head;
        for(size_t i = 0; i < pos; i++) {
            it = it->next;
        }
    } else {
        it = list->tail;
        for(size_t i = list->size - 1; i > pos; i--) {
            it = it->prev;
        }
    }

    return it;
}

void list_push_front(LinkedList *list, void *new_data, size_t data_size) {
    Node *new_node = make_node(new_data, data_size);
    
    new_node->next = list->head;
    new_node->prev = NULL;
    if(list->size == 0)
        list->tail = new_node;
    else
        list->head->prev = new_node;
    list->head=new_node;
    
    list->size++;
}

void list_pop_front(LinkedList *list) {
    Node *node = list->head;

    if(list->size == 1)
        list->tail = NULL;
    list->head = list->head->next;
    if(list->head != NULL)
        list->head->prev = NULL;

    list->size--;
    free(node->data);
    free(node);
}

void list_push_back(LinkedList *list, void *new_data, size_t data_size) {
    Node *new_node = make_node(new_data, data_size);
    
    new_node->next = NULL;
    new_node->prev = list->tail;
    if(list->size == 0)
        list->head = new_node;
    else
        list->tail->next = new_node;
    list->tail = new_node;
    
    list->size++;
}

void list_pop_back(LinkedList *list) {
    Node *node = list->tail;

    if(list->size == 1)
        list->head = NULL;
    list->tail = list->tail->prev;
    if(list->tail != NULL)
        list->tail->next = NULL;

    list->size--;
    free(node->data);
    free(node);
}


Node *list_insert(LinkedList *list, size_t pos, void *new_data, size_t data_size) {
    if(pos > list->size)
        return NULL;
    else if(pos == 0) {
        list_push_front(list, new_data, data_size);
        return list->head;
    }
    else if(pos == list->size) {
        list_push_back(list, new_data, data_size);
        return list->tail;
    }

    Node *it = list_access(list, pos - 1);
    Node *new_node = make_node(new_data, data_size);

    new_node->prev = it;
    new_node->next = it->next;
    it->next->prev = new_node;
    it->next = new_node;
    
    list->size++;
    return new_node;
}

Node *list_erase(LinkedList *list, size_t pos) {
    if(pos >= list->size)
        return NULL;
    else if(pos == 0) {
        list_pop_front(list);
        return list->head;
    } else if(pos == list->size - 1) {
        list_pop_back(list);
        return NULL;
    }

    Node *it = list_access(list, pos - 1);
    Node *del_node = it->next;

    it->next = del_node->next;
    it->next->prev = it;

    list->size--;
    free(del_node->data);
    free(del_node);
    return it->next;
}

void list_swap(LinkedList *list1, LinkedList *list2) {
    node_swap(&list1->head, &list2->head);
    node_swap(&list1->tail, &list2->tail);
    size_t_swap(&(list1->size), &(list2->size));
}

void list_resize(LinkedList *list, size_t new_size, void *new_data, size_t data_size) {
    while(new_size < list->size)
        list_pop_back(list);

    while(new_size > list->size)
        list_push_back(list, new_data, data_size);
}

void list_clear(LinkedList *list) {
    while(list->size > 0)
        list_pop_front(list);
}

void list_free(LinkedList *list) {
    list_clear(list);
    free(list);
}

void list_splice(LinkedList *dest, LinkedList *src, size_t pos, size_t first, size_t last) {
    if(pos > dest->size || first > last || last >= src->size)
        return;

    Node *src_first = list_access(src, first);
    Node *src_last = src_first;
    for(size_t i = first; i < last; i++)
        src_last = src_last->next;

    if(first == 0)
        src->head = src_last->next;
    if(last == src->size - 1)
        src->tail = src_first->prev;
    
    if(last < src->size - 1)
        src_last->next->prev = src_first->prev;
    if(first > 0)
        src_first->prev->next = src_last->next;

    Node *dest_first = NULL, *dest_last = NULL;
    if(pos > 0) {
        dest_first = list_access(dest, pos - 1);
        dest_last = dest_first->next;
    } else {
        dest_last = dest->head;
    }

    src_last->next = dest_last;
    src_first->prev = dest_first;
    if(dest_first != NULL)
        dest_first->next = src_first;
    else
        dest->head = src_first;
    if(dest_last != NULL)
        dest_last->prev = src_last;
    else
        dest->tail = src_last;

    dest->size += last - first + 1;
    src->size -= last - first + 1;
}

void list_remove(LinkedList *list, void *data, size_t data_size) {
    while(list->size > 0 && list->head->data_size == data_size && memcmp(list->head->data, data, data_size) == 0)
            list_pop_front(list);
    while(list-> size > 0 && list->tail->data_size == data_size && memcmp(list->tail->data, data, data_size) == 0)
            list_pop_back(list);

    Node *it = list->head, *next_node;
    while(it != NULL) {
        next_node = it->next;
        if(it->data_size == data_size && memcmp(it->data, data, data_size) == 0) {
            it->next->prev = it->prev;
            it->prev->next = it->next;

            list->size--;
            free(it->data);
            free(it);
        }
        it = next_node;
    }    
}

void list_remove_if(LinkedList *list, size_t data_size, int (*comp)(void *data)) {
    while(list->size > 0 && list->head->data_size == data_size && comp(list->head->data))
            list_pop_front(list);
    while(list->size > 0 && list->tail->data_size == data_size && comp(list->tail->data))
            list_pop_back(list);

    Node *it = list->head, *next_node;
    while(it != NULL) {
        next_node = it->next;
        if(it->data_size == data_size && comp(it->data)) {
            it->next->prev = it->prev;
            it->prev->next = it->next;

            list->size--;
            free(it->data);
            free(it);
        }
        it = next_node;
    }
    
}

void list_unique(LinkedList *list) {
    while(list->size > 1 && list->head->data_size == list->head->next->data_size &&
          memcmp(list->head->data, list->head->next->data, list->head->data_size) == 0)
        list_pop_front(list);
    while(list->size > 1 && list->tail->data_size == list->tail->prev->data_size &&
          memcmp(list->tail->data, list->tail->prev->data, list->tail->data_size) == 0)
        list_pop_back(list);

    Node *it = list->head, *next_node;
    while(it != NULL) {
        next_node = it->next;
        if(next_node != NULL && next_node->data_size == it->data_size &&
           memcmp(next_node->data, it->data, it->data_size) == 0) {
            next_node->prev = it->prev;
            it->prev->next = next_node;

            list->size--;
            free(it->data);
            free(it);
        }
        it = next_node;
    }
}

void list_merge(LinkedList *src, LinkedList *dest, int (*comp)(void *, void *)) {
    if(src->size == 0) {
        list_swap(src, dest);
        list_free(dest);
        return;
    }
    if(dest->size == 0) {
        list_free(dest);
        return;
    }

    LinkedList *out = list_init();
    Node *src_it = src->head, *dest_it = dest->head, *node;

    if(comp(src_it->data, dest_it->data)) {
        out->tail = out->head = src_it;
        src_it = src_it->next;
    } else {
        out->tail = out->head = dest_it;
        dest_it = dest_it->next;
    }

    while(src_it != NULL && dest_it != NULL) {
        if(comp(src_it->data, dest_it->data) == 1) {
            node = src_it;
            src_it = src_it->next;
        } else {
            node = dest_it;
            dest_it = dest_it->next;
        }

        node->prev = out->tail;
        out->tail->next = node;
        out->tail = node;
    }

    if(src_it != NULL) {
        src_it->prev = out->tail;
        out->tail->next = src_it;
        out->tail= src->tail;
    } else {
        dest_it->prev = out->tail;
        out->tail->next = dest_it;
        out->tail = dest->tail;
    }

    out->size = src->size + dest->size;
    out->tail->next = NULL;
    src->head = src->tail = NULL;
    src->size = 0;
    dest->head = dest->tail = NULL;
    dest->size = 0;
    list_swap(src, out);
    list_free(out);
    list_free(dest);
}

void list_split(LinkedList *list, LinkedList **p_left, LinkedList **p_right, size_t split_pos) {
    if(split_pos == 0 || split_pos >= list->size)
        return;

    LinkedList *left = list_init();
    LinkedList *right = list_init();
    Node *split_node = list_access(list, split_pos);
    
    left->head = list->head;
    left->tail = split_node->prev;
    left->tail->next = NULL;

    right->head = split_node;
    right->tail = list->tail;
    right->head->prev = NULL;

    left->size = split_pos;
    right->size = list->size - split_pos;
    list->size = 0;
    list->head = list->tail = NULL;
    list_free(list);

    *p_left = left;
    *p_right = right;
}

void list_sort(LinkedList **p_list, int (*comp)(void *, void *)) {
    LinkedList *list = *p_list;
    if(list->size < 2)
        return;

    LinkedList *left, *right;
    list_split(list, &left, &right, list->size / 2);
    
    list_sort(&left, comp);
    list_sort(&right, comp);

    list_merge(left, right, comp);
    *p_list = list_init();
    list_swap(*p_list, left);
    list_free(left);
}

void list_reverse(LinkedList *list) {
    Node *left = list->head, *right = list->tail;
    for(size_t i = 0; i < list->size / 2; i++) {
        void_swap(&left->data, &right->data);
        left = left->next;
        right = right->prev;
    }
}
