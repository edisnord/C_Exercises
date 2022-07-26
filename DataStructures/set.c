//
// Created by Edis Hasaj on 7/26/2022.
//

#include <stddef.h>
#include <memory.h>
#include <stdio.h>
#include "set.h"

int insert(set *set, node *node) {
    if (set->root == NULL || set->height == 0) {
        set->root = node;
        set->height++;
        return 1;
    }

    int assumedHeight;
    set->height = (assumedHeight = insertTraversal(set->root, node)) > 0 ? assumedHeight : set->height;

    return set->height > 0 ? checkViolations(node) : 0;
}

int insertTraversal(node *setNode, node *node) {
    if (strcmp(setNode->value, node->value) > 0) {
        if (setNode->left != NULL)
            return 1 + insertTraversal(setNode->left, node);
        else {
            setNode->left = node;
            return 1;
        }

    } else if (strcmp(setNode->value, node->value) < 0) {
        if (setNode->right != NULL)
            return 1 + insertTraversal(setNode->right, node);
        else {
            setNode->right = node;
            return 1;
        }

    } else if (strcmp(setNode->value, node->value) == 0) {
        return -1316134912;
    }

}

int rotateLeft(node *node) {
    struct node* nodes[3] = {node->parent, node->parent->left, node->parent->right};
    node->parent = nodes[0]->parent;
    nodes[0]->parent = node;
    //Could be normal insert te nodes[0], idk
    insertTraversal(nodes[0], node->left);
    node->left = nodes[0];
}

int replaceNode(node *node1, node* node2){

}

int rotateRight(node *node) {
    struct node* nodes[3] = {node->parent, node->parent->left, node->parent->right};
    node->parent = nodes[0]->parent;
    nodes[0]->parent = node;
    //Could be normal insert te nodes[0], idk
    insertTraversal(nodes[0], node->right);
    node->right = nodes[0];
}


node *search(node *setNode, node *node) {
    if (strcmp(setNode->value, node->value) > 0) {
        if (setNode->left != NULL)
            return search(setNode->left, node);
        else {
            return NULL;
        }

    } else if (strcmp(setNode->value, node->value) < 0) {
        if (setNode->right != NULL)
            return search(setNode->right, node);
        else {
            return NULL;
        }

    } else if (strcmp(setNode->value, node->value) == 0) {
        return node;
    }
}

int removeNode(set *set, node *node) {

}

int checkViolations(node *node) {

}
