#include "chapter6.h"

int main(){

    char* a = malloc(1000 * sizeof(char));
    strcpy(a, "  asdwf  ");
    cleanName(&a);
    puts(a);

    parseDecl("../chapter_3.c", 2);

}

