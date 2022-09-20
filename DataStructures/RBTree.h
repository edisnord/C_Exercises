//
// Created by Edis Hasaj on 9/20/2022.
//

#ifndef TEST_RBTREE_H
#define TEST_RBTREE_H

typedef struct node {
    struct node *parent;
    struct node *left;
    struct node *right;
    void *value;
    short color;
} node;

typedef int (*comparator)(const void *, const void *);

typedef struct rbTree {
    node *root;
    int height;
    unsigned long valSize;
    comparator comparator;
} rbTree;

enum colors {
    RED, BLACK
};

enum violations {
    NONE, RIGHT_UNCLE_RED, RIGHT_UNCLE_BLACK, LEFT_UNCLE_RED, LEFT_UNCLE_BLACK, ROOT
};

enum positions {
    L, R
};

enum imbalances {
    RR, RL, LL, LR
};

rbTree *newRBTree(comparator comparator, unsigned long valSize);

int insertRBTree(rbTree *tree, void* value, int num);

int searchRBTree(rbTree *tree, void *value);

void freeTree(rbTree* tree);

#endif //TEST_RBTREE_H
