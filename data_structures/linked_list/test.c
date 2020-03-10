#include <stdio.h>
#include "LinkedList.h"

int main() {

    //TEST #1
    printf("TEST #1:\n");
    int x = 3;
    double y = 2.73;
    char f = 'c';
    char *w = "gabi";

    LinkedList *list = list_init();

    list_push_back(list, &x, sizeof(x));
    list_push_back(list, &y, sizeof(y));
    list_push_back(list, &f, sizeof(f));
    list_push_back(list, w, sizeof(w));

    Node *it = list->head;

    printf("%d ", *(int *)it->data);
    it = it->next;
    printf("%f ", *(double *)it->data);
    it = it->next;
    printf("%c ", *(char *)it->data);
    it = it->next;
    printf("%s\n", (char *)it->data);

    list_free(list);

    //TEST #2
    printf("\nTEST #2:\n");
    list = list_init();

    int odd[5] = {1, 3, 5, 7, 9};
    list_insert(list, 0, &odd[1], sizeof(odd[1]));
    list_insert(list, 0, &odd[1], sizeof(odd[1]));
    list_insert(list, 0, &odd[1], sizeof(odd[1]));
    for(int i = 0; i < 5; i++) {
        list_insert(list, i+1, &odd[i], sizeof(odd[i]));
    }

    list_erase(list, 1);
    list_erase(list, 5);
    
    for(Node *it = list->head; it != NULL; it = it->next) {
        printf("%d ", *(int *)it->data);
    }
    printf("\n");

    list_free(list);
    
    //TEST #3
    printf("\nTEST #3:\n");
    list = list_init();
    LinkedList *list2 = list_init();
    int digits[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for(int i = 0; i < 10; i++) {
        list_insert(list, 0, &digits[i], sizeof(digits[i]));
    }
    for(int i = 0; i < 5; i++) {
        list_insert(list2, 0, &digits[2*i], sizeof(digits[2*i]));
    }
    
    list_swap(list,list2);
    list_resize(list, 15, sizeof(int));
    list_resize(list2, 3, sizeof(int));
    
    for(Node *it = list->head; it != NULL; it = it->next) {
        printf("%d ", *(int *)it->data);
    }
    printf("\n");
    for(Node *it = list2->head; it != NULL; it = it->next) {
        printf("%d ", *(int *)it->data);
    }
    printf("\n");

    list_free(list);
    list_free(list2);

    return 0;
}
