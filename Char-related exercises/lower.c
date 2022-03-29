#include "lower.h"

char changeCase(char letter){
    return (letter >= 'a') ? letter - 32 : letter + 32;
}

char lower(char letter){
    return (letter >= 'a' && letter <= 'z') ? letter - 32 : '\0';
}