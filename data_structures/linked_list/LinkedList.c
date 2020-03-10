#include "LinkedList.h"

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
    Node *aux_node;
    size_t aux_size;

    aux_node = list1->head;
    list1->head = list2->head;
    list2->head = aux_node;

    aux_node = list1->tail;
    list1->tail = list2->tail;
    list2->tail = aux_node;

    aux_size = list1->size;
    list1->size = list2->size;
    list2->size = aux_size;
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
    Node *dest_pos, *src_first, *src_last;
    size_t i;

    if(dest == NULL || src == NULL) {
        return;
    }
    if(pos > dest->size || first > last || last >= src->size) {
        return;
    }

    if(pos > 0) {
        dest_pos = list_access(dest, pos - 1);
    }
    src_first = list_access(src, first);
    src_last = src_first;
    dest->size += last - first + 1;
    src->size -= last - first + 1;

    for(i = first; i < last; i++) {
        src_last = src_last->next;
    }
    
    if(src_first->prev != NULL) {
        src_first->prev->next = src_last->next;
    } else {
        src->head = src_last->next;
    }
    if(src_last->next != NULL) {
        src_last->next->prev = src_first->prev;
    } else {
        src->tail = src_first->prev;
    }

    if(pos == 0) {
        src_first->prev = NULL;
        src_last->next = dest->head;
        dest->head->prev = src_last;
        dest->head = src_first;
        return;
    }

    if(pos == dest->size) {
        src_first->prev = dest->tail;
        src_last->next = NULL;
        dest->tail->next = src_first;
        dest->tail = src_last;
        return;
    }

    src_first->prev = dest_pos;
    src_last->next = dest_pos->next;
    dest_pos->next->prev = src_last;
    dest_pos->next = src_first;
}
