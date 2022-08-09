//#include "chapter6.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "DataStructures/set.h"

//void seeMatching(char** array, int num, int matching){
//    char** finalArray
//    for (int i = 0; i < matching; ++i) {
//        char* current = malloc(strlen(array[i]) * sizeof(char));
//        strcpy(current, array[i]);
//        current[matching] = '\0';
//
//        for (int j = 0; j < matching; ++j) {
//            char* needle = strstr(array[j], current);
//            if(needle == array[j]){
//
//            }
//        }
//    }
//}

int main() {


    set set1 = {NULL, 0};

    char *nodes[] = {"Quick",
                     "Brown",
                     "The",
                     "Fox",
                     "Jumped",
                     "Over",
                     "The",
                     "Shit",
                     "Lazy",
                     "Brown",
                     "Dog"};

    for (int i = 0; i < 10; ++i) {
        insertSet(&set1, nodes[i]);
    }

    puts(searchSet(set1.root, "Jumped")->value);

}

