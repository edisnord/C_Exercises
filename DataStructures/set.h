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

typedef struct node {
    struct node *parent;
    struct node *left;
    struct node *right;
    char *value;
    short color;
} node;


typedef struct set {
    struct node *root;
    int height;
} set;

int getPositionRelativeToParent(node* node);

node *newNullNode(node* parent);

node* newTreeNode(char *val);

int insertSet(set *set, char *val);

int insertNodeBT(node *setNode, node *node);

node * rotateLeftBT(node *root);

int checkImbalanceCategoryRBT(node *subtreeRoot, int pos1);

node * rotateRightBT(node *root);

//Mir ben ti implementosh kto height functions
int computeHeightBT(set *set);

int computeBlackHeightRBT(set *set);

node *searchSet(node *setNode, char *string);

int removeSet(set *set, char *string);

int fixViolations(node *node);

int checkViolation(node *node);

#endif //TEST_SET_H
