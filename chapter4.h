//
// Created by edish on 22-05-11.
//

#ifndef TEST_CHAPTER4_H
#define TEST_CHAPTER4_H
#include <ctype.h>

//4-14
#define SWAP(t, x, y) {\
                    t temp = *x;\
                    *x = *y;\
                    *y = temp;\
                }

//4-1
int strindex(const char s[], const char t[]);

//4-12
void recursiveitoa(char a[], int num ,int count);

//4-13
void reverse(char** string);

//4-2
//float atof(char s[]);

#endif //TEST_CHAPTER4_H
