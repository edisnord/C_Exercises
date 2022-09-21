//
// Created by Edis Hasaj on 9/20/2022.
//

#ifndef TEST_RBTREE_H
#define TEST_RBTREE_H

typedef struct node node;
typedef struct rbTree rbTree;
#ifndef CMP
#define CMP
typedef int (*comparator)(const void *, const void *);
#endif


rbTree *newRBTree(comparator comparator, unsigned long valSize);

int insertRBTree(rbTree *tree, void* value, int num);

int existsRBTree(rbTree *tree, void *value);

void* getRBTree(rbTree* tree, void *value);

void freeRBTree(rbTree* tree);

#endif //TEST_RBTREE_H
