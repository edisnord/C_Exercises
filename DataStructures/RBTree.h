//
// Created by Edis Hasaj on 9/20/2022.
//

#ifndef TEST_RBTREE_H
#define TEST_RBTREE_H

typedef struct node node;
typedef struct rbTree rbTree;
typedef int (*comparator)(const void *, const void *);

rbTree *newRBTree(comparator comparator, unsigned long valSize);

int insertRBTree(rbTree *tree, void* value, int num);

int searchRBTree(rbTree *tree, void *value);

void freeTree(rbTree* tree);

#endif //TEST_RBTREE_H
