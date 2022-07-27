//
// Created by Edis Hasaj on 7/26/2022.
//

#include "set.h"

enum colors {
    RED, BLACK
};

enum violations {
    NONE, RIGHT_UNCLE_RED, RIGHT_UNCLE_BLACK, LEFT_UNCLE_RED, LEFT_UNCLE_BLACK, GRANDPARENT_NULL
};

//Returns pointer to heap-allocated node structure
node *newSetNode(char *val) {
    node *nodePtr = malloc(sizeof(node));
    nodePtr->value = malloc(sizeof(char) * strlen(val));
    strcpy(nodePtr->value, val);
    nodePtr->parent = NULL;
    nodePtr->left = NULL;
    nodePtr->right = NULL;
    nodePtr->color = RED;
    return nodePtr;
}

int insertSet(set *set, node *node) {
    if (set->root == NULL || set->height == 0) {
        node->color = BLACK;
        set->root = node;
        set->height++;
        return 1;
    }

    int assumedHeight;
    set->height = (assumedHeight = insertTraversal(set->root, node)) > 0 ? assumedHeight : set->height;


    return set->height > 0 ? fixViolations(node) : 0;
}

int insertTraversal(node *setNode, node *node) {
    if (strcmp(setNode->value, node->value) > 0) {
        if (setNode->left != NULL)
            return 1 + insertTraversal(setNode->left, node);
        else {
            node->parent = setNode;
            setNode->left = node;
            return 1;
        }

    } else if (strcmp(setNode->value, node->value) < 0) {
        if (setNode->right != NULL)
            return 1 + insertTraversal(setNode->right, node);
        else {
            node->parent = setNode;
            setNode->right = node;
            return 1;
        }

    } else if (strcmp(setNode->value, node->value) == 0) {
        return -1316134912;
    }

}

int rotateLeft(node *node) {
    struct node *child = node->left;
    struct node *leftChild = child->left;
    child->parent = node->parent;
    child->left = node->parent;
    insertTraversal(child->parent, leftChild);
    if (checkViolation(leftChild))
        fixViolations(leftChild);
}

int rotateRight(node *node) {
    struct node *child = node->left;
    struct node *rightChild = child->right;
    child->parent = node->parent;
    child->right = node->parent;
    insertTraversal(child->parent, rightChild);
    if (checkViolation(rightChild))
        fixViolations(rightChild);
}

node *searchSet(node *setNode, char *string) {
    if (strcmp(setNode->value, string) > 0) {
        if (setNode->left != NULL)
            return searchSet(setNode->left, string);
        else {
            return NULL;
        }

    } else if (strcmp(setNode->value, string) < 0) {
        if (setNode->right != NULL)
            return searchSet(setNode->right, string);
        else {
            return NULL;
        }

    } else if (strcmp(setNode->value, string) == 0) {
        return setNode;
    }
}

int removeSet(set *set, char *string) {

}

int fixViolations(node *node) {

    struct node *grandparent;
    if (node->parent == NULL) {
        node->color = BLACK;
    }
    switch (checkViolation(node)) {
        case RIGHT_UNCLE_RED: {
            grandparent = node->parent->parent;
            grandparent->color = BLACK;
            grandparent->right->color = BLACK;
            grandparent->color = RED;
            break;
        }
        case RIGHT_UNCLE_BLACK: {
            grandparent = node->parent->parent;
            rotateRight(grandparent);
            short tempColor = node->parent->color;
            node->parent->color = grandparent->color;
            grandparent->color = tempColor;
            break;
        }
        case LEFT_UNCLE_RED: {
            grandparent = node->parent->parent;
            grandparent->color = BLACK;
            grandparent->left->color = BLACK;
            grandparent->color = RED;
            break;
        }
        case LEFT_UNCLE_BLACK: {
            grandparent = node->parent->parent;
            rotateLeft(grandparent);
            short tempColor = node->parent->color;
            node->parent->color = grandparent->color;
            grandparent->color = tempColor;
            break;
        }
    }
    return 1;
}

/*
 * Violation codes:
 * 0 -> no violation
 * 1 -> right uncle red
 * 2 -> right uncle black
 * 3 -> left uncle red
 * 4 -> left uncle black
 * 5 -> grandfather is null
 */
int checkViolation(node *node) {
    struct node *grandparent = NULL;
    if (node->parent == NULL) {
        return GRANDPARENT_NULL;
    }

    if (node->parent->parent != NULL && node->parent->color == RED) {
        grandparent = node->parent->parent;
        if (grandparent->left != NULL) {
            if (grandparent->left == node->parent && grandparent->right != NULL) {    //Case left child
                if (grandparent->right->color == RED)
                    return RIGHT_UNCLE_RED;
                else
                    return RIGHT_UNCLE_BLACK;
            }
        } else if (grandparent->right != NULL) {
            if (grandparent->right == node->parent && grandparent->left != NULL) {
                if (grandparent->left->color == RED)
                    return LEFT_UNCLE_RED;
                else
                    return LEFT_UNCLE_BLACK;
            }
        }
    } else {
        if (grandparent == NULL) return GRANDPARENT_NULL;
    }
    return NONE;
}