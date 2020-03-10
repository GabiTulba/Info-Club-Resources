#include <stdio.h>
#include <stdlib.h>
#include "List.h"

#define MOD 666013
#define MAXVAL 18000000

int a1, a2, a3, a4, a5;

List *HashTable[MOD];

void Initialize(){
    for(int i = 0; i < MOD; ++ i)
        HashTable[i] = createList();
}

void Destroy(){
    for(int i = 0; i < MOD; ++ i)
        destroyList(HashTable[i]);
}

int main(int argc, const char * argv[]) {
    
    FILE *in = fopen("eqs.in", "r");
    FILE *out = fopen("eqs.out", "w");
    
    fscanf(in, "%d %d %d %d %d", &a1, &a2, &a3, &a4, &a5);
    
    Initialize();
    
    for(int X1 = -50; X1 <= 50; ++ X1){
        for(int X2 = -50; X2 <= 50; ++ X2){
            if(X1 == 0 || X2 == 0)
                continue;
            int value = 1LL * X1 * X1 * X1 * a1 + 1LL * X2 * X2 * X2 * a2;
            value += MAXVAL;
            int valueMod = value % MOD;
            addElem(HashTable[valueMod], value);
        }
    }
    
    int noSolutions = 0;
    for(int X3 = -50; X3 <= 50; ++ X3){
        for(int X4 = -50; X4 <= 50; ++ X4){
            for(int X5 = -50; X5 <= 50; ++ X5){
                if(X3 == 0 || X4 == 0 || X5 == 0)
                    continue;
                int value = 1LL * X3 * X3 * X3 * a3 + 1LL * X4 * X4 * X4 * a4 + 1LL * X5 * X5 * X5 * a5;
                value += MAXVAL;
                int valueMod = value % MOD;
                noSolutions += getAppearances(HashTable[valueMod], value);
            }
        }
    }
    
    fprintf(out, "%d", noSolutions);
    
    Destroy();
    
    return 0;
}
