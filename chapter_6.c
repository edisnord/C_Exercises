#include <malloc.h>
#include "chapter_6.h"
#include "string.h"

void parseVars(char* code, int chars){
    size_t size = buflen;
    char* line = malloc(sizeof(char) * buflen);
    FILE* file = fopen(code, "r");
    char** variables;
    while (getline(&line, &size, file) != -1){
        
    }

}