#include <stdio.h>
#include <stdlib.h>
#include "List.h"

#define MOD 666013

int noTests, value, type;

List* HashTable[MOD];

void Initialize(){
    for(int i = 0; i < MOD; ++ i)
        HashTable[i] = createList();
}

void Destroy(){
    for(int i = 0; i < MOD; ++ i)
        destroyList(HashTable[i]);
}

int main(int argc, const char * argv[]) {
    
    FILE* in = fopen("hashuri.in", "r");
    FILE* out = fopen("hashuri.out", "w");
    
    fscanf(in, "%d", &noTests);
    
    Initialize();
    
    for(int testCrt = 0; testCrt < noTests; ++ testCrt){
        fscanf(in, "%d %d", &type, &value);
        int valueMod = value % MOD;
        switch(type){
            case 1:
                if(!checkIfExists(HashTable[valueMod], value)){
                    addElem(HashTable[valueMod], value);
                }
                break;
            case 2:
                delElem(HashTable[valueMod], value);
                break;
            case 3:
                fprintf(out, "%d\n", checkIfExists(HashTable[valueMod], value));
                break;
        }
    }
    
    Destroy();
    
    return 0;
}
