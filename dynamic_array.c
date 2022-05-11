#include <malloc.h>
#include "stdio.h"

char* create_space(){
    char* point = calloc(0, sizeof (char));
    return point;
}

void addAndReallocate(char* arr, char new, int* lenLoc){
    *lenLoc = *lenLoc + 1;
    arr = realloc(arr, sizeof (char) * *lenLoc);
    *(arr+*lenLoc-1) = new;
}

void removeLast(char* arr, int* lenLoc){
    *lenLoc -= 1;
    arr = realloc(arr, sizeof (char ) * *lenLoc);
}

void clear(char* clear){
    clear = realloc(0,0);
}