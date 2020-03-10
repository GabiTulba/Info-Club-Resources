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

    //TEST#2
    printf("\nTEST #2:\n");
    list = list_init();

    int odd[5] = {1, 3, 5, 7, 9}, a;
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
    return 0;
}
