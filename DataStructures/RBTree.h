//
// Created by Edis Hasaj on 9/20/2022.
//

#ifndef TEST_RBTREE_H
#define TEST_RBTREE_H

typedef struct node node;
typedef struct rbTree rbTree;
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "DoublyLinkedList.h"

#ifndef CMP
#define CMP
typedef int (*comparator)(const void *, const void *);
#endif


DoublyLinkedList * flattenRBTree(rbTree* tree);

rbTree *newRBTree(comparator comparator, unsigned long valSize);

bool isEmptyRBTree(rbTree *tree);

int insertRBTree(rbTree *tree, void* value, int num);

int existsRBTree(rbTree *tree, void *value);

void* getRBTree(rbTree* tree, void *value);

void freeRBTree(rbTree* tree);

#endif //TEST_RBTREE_H
