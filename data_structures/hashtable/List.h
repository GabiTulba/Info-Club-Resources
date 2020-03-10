#ifndef List_h
#define List_h

typedef struct ListNode{
    int value;
    struct ListNode *next;
}ListNode;

typedef struct List{
    struct ListNode *root;
}List;

List * createList(){
    List *newList = (List *)calloc(1, sizeof(List));
    return newList;
}

void addElem(List *list, int value){
    if(list == NULL)
        return;
    ListNode *newNode = (ListNode *)calloc(1, sizeof(ListNode));
    newNode->value = value;
    if(list->root == NULL){
        list->root = newNode;
    }
    else{
        newNode->next = list->root;
        list->root = newNode;
    }
}

void delElem(List *list, int value){
    if(list == NULL || list->root == NULL)
        return;
    if(list->root->next == NULL && list->root->value == value){
        free(list->root);
        list->root = NULL;
    }
    else{
        ListNode *crtNode = list->root;
        ListNode *antNode = NULL;
        while(crtNode != NULL){
            if(crtNode->value == value){
                if(antNode == NULL){
                    list->root = crtNode->next;
                }
                else{
                    antNode->next = crtNode->next;
                }
                free(crtNode);
            }
            antNode = crtNode;
            crtNode = crtNode->next;
        }
    }
}

int checkIfExists(List *list, int value){
    if(list == NULL)
        return 0;
    ListNode *crtNode = list->root;
    while(crtNode != NULL){
        if(crtNode->value == value)
            return 1;
        crtNode = crtNode->next;
    }
    return 0;
}

int getAppearances(List *list, int value){
    if(list == NULL)
        return 0;
    ListNode *crtNode = list->root;
    int appearance = 0;
    while(crtNode != NULL){
        if(crtNode->value == value)
            appearance ++;
        crtNode = crtNode->next;
    }
    return appearance;
}

void destroyList(List *list){
    if(list == NULL)
        return;
    ListNode *crtNode = list->root;
    while(crtNode != NULL){
        ListNode *aux = crtNode->next;
        free(crtNode);
        crtNode = aux;
    }
    free(list);
}



#endif
