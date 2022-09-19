//
// Created by edish on 22-09-19.
//

#ifndef TEST_CHAPTER6_UTIL_H
#define TEST_CHAPTER6_UTIL_H


void trim(char **string);

int cleanName(char **name);

char *substring(char *string, int start, int end);

void sortNamesAscending(char ***names, int num);

int comparator(const void *a, const void *b);

#include "chapter6.h"

#endif //TEST_CHAPTER6_UTIL_H
