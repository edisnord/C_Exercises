//
// Created by Edis Hasaj on 7/26/2022.
//

//Set structure that holds strings, traversed with strcmp

#ifndef TEST_SET_H
#define TEST_SET_H

typedef struct node {
    struct node *parent;
    struct node *left;
    struct node *right;
    char* value;
    short color;
} node;


typedef struct set{
    struct node* root;
    int height;
} set;

int insert(set* set, node* node);
int insertTraversal(node* setNode, node* node);
int rotateLeft(node *node);
int rotateRight(node *node);
int computeHeight(set* set, node* node);
node * search(node *setNode, node* node);
int removeNode(set* set, node* node);
int checkViolations(node *node);
int replaceNode(node *node1, node* node2);

#endif //TEST_SET_H
