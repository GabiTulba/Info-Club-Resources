#include "LinkedList.h"

LinkedList *list_init() {
    LinkedList *list = (LinkedList *) malloc(sizeof(LinkedList));
    
    list->head = list->tail = NULL;
    list->size = 0;
    
    return list;
}

size_t list_get_size(LinkedList *list) {
    if(list == NULL) {
        return 0;
    }

    return list->size;
}

int list_is_empty(LinkedList *list) {
    if(list == NULL) {
        return 1;
    }

    return list->size == 0;
}

Node *list_front(LinkedList *list) {
    if(list == NULL) {
        return NULL;
    }

    return list->head;
}

Node *list_back(LinkedList *list) {
    if(list == NULL) {
        return NULL;
    }

    return list->tail;
}

Node *list_access(LinkedList *list, size_t pos) {
    size_t i;
    Node *it;

    if(list == NULL || pos >= list->size) {
        return NULL;
    }

    if(pos < list->size / 2) {
        it = list->head;
        
        for(i = 0; i < pos; i++) {
            it = it->next;
        }
    } else {
        it = list->tail;
        for(i = list->size - 1; i > pos; i--) {
            it = it->prev;
        }
    }

    return it;
}

void list_push_front(LinkedList *list, void *new_data, size_t data_size) {
    Node *new_node;

    if(list == NULL) {
        return;
    }

    new_node = (Node *) malloc(sizeof(Node));
    new_node->data = malloc(data_size);
    new_node->data_size = data_size;
    memcpy(new_node->data, new_data, data_size);
    new_node->next = list->head;
    new_node->prev = NULL;
    if(list->size == 0) {
        list->head = list->tail = new_node;
    } else {
        list->head->prev = new_node;
        list->head = new_node;
    }
    list->size++;
}

void list_pop_front(LinkedList *list) {
    Node *node;

    if(list == NULL) {
        return;
    }

    if(list->size == 1) {
        node = list->head;
        list->head = list->tail = NULL;
        free(node->data);
        free(node);
        list->size--;
        return;
    }

    node = list->head;
    list->head = list->head->next;
    list->head->prev = NULL;
    free(node->data);
    free(node);
    list->size--;
}

void list_push_back(LinkedList *list, void *new_data, size_t data_size) {
    Node *new_node;

    if(list == NULL) {
        return;
    }

    new_node = (Node *) malloc(sizeof(Node));
    new_node->data = malloc(data_size);
    new_node->data_size = data_size;
    memcpy(new_node->data, new_data, data_size);
    new_node->next = NULL;
    new_node->prev = list->tail;
    if(list->size == 0) {
        list->head = list->tail = new_node;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }
    list->size++;
}

void list_pop_back(LinkedList *list) {
    Node *node;

    if(list == NULL) {
        return;
    }

    if(list->size == 1) {
        node = list->head;
        list->head = list->tail = NULL;
        free(node->data);
        free(node);
        list->size--;
        return;
    }

    node = list->tail;
    list->tail = list->tail->prev;
    list->tail->next = NULL;
    free(node->data);
    free(node);
    list->size--;
}

Node *list_insert(LinkedList *list, size_t pos, void *new_data, size_t data_size) {
    Node *new_node, *it;
    size_t i;

    if(list == NULL || pos > list->size) {
        return NULL;
    }

    if(pos == 0) {
        list_push_front(list, new_data, data_size);
        return list->head;
    } else if(pos == list->size) {
        list_push_back(list, new_data, data_size);
        return list->tail;
    }

    new_node = (Node *) malloc(sizeof(Node));
    new_node->data = malloc(sizeof(data_size));
    new_node->data_size = data_size;
    memcpy(new_node->data, new_data, data_size);

    if(pos < list->size / 2) {
        it = list->head;
        for(i = 0; i < pos - 1; i++) {
            it = it->next;
        }

        new_node->prev = it;
        new_node->next = it->next;
        it->next->prev = new_node;
        it->next = new_node;
    } else {
        it = list->tail;
        for(i = list->size - 1; i > pos + 1; i--) {
            it = it->prev;
        }

        new_node->next = it;
        new_node->prev = it->prev;
        it->prev->next = new_node;
        it->prev = new_node;
    }
    
    list->size++;
    return new_node;
}

Node *list_erase(LinkedList *list, size_t pos) {
    Node *it, *node;
    size_t i;

    if(list == NULL || pos >= list->size) {
        return NULL;
    }

    if(pos == 0) {
        list_pop_front(list);
        return list->head;
    } else if(pos == list->size - 1) {
        list_pop_back(list);
        return NULL;
    }

    if(pos < list->size / 2) {
        it = list->head;
        for(i = 0; i < pos - 1; i++) {
            it = it->next;
        }

        node = it->next;
        it->next = node->next;
        it->next->prev = it;
        it = it->next;
    } else {
        it = list->tail;
        for(i = list->size -1; i > pos +1; i--) {
            it = it->prev;
        }

        node = it->prev;
        it->prev = node->prev;
        it->prev->next = it;
    }
    free(node->data);
    free(node);
    list->size--;
    return it;
}

void list_swap(LinkedList *list1, LinkedList *list2) {
    Node *aux_node;
    size_t aux_size;
    void *aux_data;

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

void list_resize(LinkedList *list, size_t new_size, size_t data_size) {
    void *empty_data;

    while(new_size < list->size) {
        list_pop_back(list);
    }

    empty_data = calloc(1, sizeof(data_size));
    while(new_size > list->size) {
        list_push_back(list, empty_data, data_size);
    }

    free(empty_data);
}

void list_clear(LinkedList *list) {
    if(list == NULL) {
        return;
    }

    while(list->size > 0) {
        list_pop_front(list);
    }
}

void list_free(LinkedList *list) {
    if(list == NULL) {
        return;
    }

    list_clear(list);
    free(list);
}
