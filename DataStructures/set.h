//
// Created by Edis Hasaj on 7/26/2022.
//

//Set structure that holds strings, traversed with strcmp

#ifndef TEST_SET_H
#define TEST_SET_H

#include <stddef.h>
#include <memory.h>
#include <stdio.h>
#include "stdlib.h"
#include "RBTree.h"

typedef struct set set;

struct set_vtable{
    int* (*insert)(set* set, void* insertion, unsigned long sizeOfDatatype, int arrLen);
    int* (*search)(set* set, void* element);
    void* (*free)(set* set);
};

typedef struct set {
    int height;
    struct set_vtable vtable;
    rbTree* tree;
} set;

int insertSet(set *set, void *val, unsigned long sizeOfDatatype, int arrLen);

int searchSet(set* set, void *value);

void freeSet(set *set);

set* newSet(comparator, unsigned long valSize);

#endif //TEST_SET_H
