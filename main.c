//#include "chapter6.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"

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



int main(){

    char* a = malloc(1000 * sizeof(char));
    strcpy(a, "  asdwf  ");
    //cleanName(&a);
    puts(a);

    putc(strcmp("bbb", "aaa") + '0', stdout);

    //parseDecl("../chapter_3.c", 2);

}

