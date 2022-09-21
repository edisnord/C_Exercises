//
// Created by Edis Hasaj on 9/20/2022.
//

#include "RBTree.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

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

typedef struct node {
    struct node *parent;
    struct node *left;
    struct node *right;
    void *value;
    short color;
} node;


typedef struct rbTree {
    node *root;
    int height;
    unsigned long valSize;
    comparator comparator;
} rbTree;

node *rotateLeftBT(node *root);

int checkImbalanceCategoryRBT(node *subtreeRoot, int pos1);

node *rotateRightBT(node *root);

void freeNodesBelow(node *node);

void freeNode(node *node);

int getPositionRelativeToParent(node *node);

node *newNullNode(node *parent);

node *newTreeNode(rbTree *tree, void *val, int num);

node *determineRoot(node *node);

int fixViolations(node *node);

int checkViolation(node *node);

node *searchNodes(rbTree *tree, node *setNode, void *value);

int insertNodeBT(rbTree *tree, node *setNode, node *node);

int existsRBTree(rbTree *tree, void *value) {
    return searchNodes(tree, tree->root, value) == NULL ? false : true;
}

void* getRBTree(rbTree* tree, void *value){
        node* node = searchNodes(tree, tree->root, value);
        return node == NULL ? NULL : node->value;
}

int insertRBTree(rbTree *tree, void *value, int num) {
    node *node = newTreeNode(tree, value, 0);
    if (tree->root == NULL || tree->height == 0) {
        node->color = BLACK;
        tree->root = node;
        tree->height++;
        return 1;
    }

    int assumedHeight;
    int result = (assumedHeight = insertNodeBT(tree, tree->root, node)) > 0 ? true : false;
    fixViolations(node);
    tree->root = determineRoot(node);
    return result;
}

rbTree *newRBTree(comparator comparator, unsigned long valSize) {
    rbTree *tree = malloc(sizeof(rbTree));
    *tree = (struct rbTree) {NULL, 0, valSize, comparator};
    return tree;
}

int getPositionRelativeToParent(node *node) {
    return node == node->parent->left ? L : R;
}

node *newNullNode(node *parent) {
    node *nodePtr = malloc(sizeof(node));
    nodePtr->value = NULL;
    nodePtr->parent = parent;
    nodePtr->left = NULL;
    nodePtr->right = NULL;
    nodePtr->color = BLACK;
    return nodePtr;
}

//Returns pointer to heap-allocated node structure
node *newTreeNode(rbTree *tree, void *val, int num) {
    node *nodePtr = malloc(sizeof(node));
    if (nodePtr == NULL) {
        fprintf(stderr, "No more MALLOC space!");
    }
    memcpy(nodePtr->value = malloc(tree->valSize * num), val, tree->valSize);
    nodePtr->parent = NULL;
    nodePtr->left = newNullNode(nodePtr);
    nodePtr->right = newNullNode(nodePtr);
    nodePtr->color = RED;
    return nodePtr;
}

node *determineRoot(node *node) {
    if (node->parent == NULL)
        return node;
    else
        return determineRoot(node->parent);
}

int insertNodeBT(rbTree *tree, node *setNode, node *node) {
    if (tree->comparator(setNode->value, node->value) > 0) {
        if (setNode->left->value != NULL)
            return 1 + insertNodeBT(tree, setNode->left, node);
        else {
            free(setNode->left);
            node->parent = setNode;
            setNode->left = node;
            return 1;
        }

    } else if (tree->comparator(setNode->value, node->value) < 0) {
        if (setNode->right->value != NULL)
            return 1 + insertNodeBT(tree, setNode->right, node);
        else {
            free(setNode->right);
            node->parent = setNode;
            setNode->right = node;
            return 1;
        }

    } else if (tree->comparator(setNode->value, node->value) == 0) {
        return -1316134912;
    }

}

//Left rotation rooted at parameter node "root"
node *rotateLeftBT(node *root) {
    node *pivot = root->right;
    if (root->parent != NULL) {
        if (getPositionRelativeToParent(root) == R)
            root->parent->right = pivot;
        else
            root->parent->left = pivot;
    }
    root->right = pivot->left;
    root->right->parent = root;
    pivot->left = root;
    pivot->parent = root->parent;
    root->parent = pivot;
    return pivot;
}

//Right rotation rooted at parameter root "root"
node *rotateRightBT(node *root) {
    node *pivot = root->left;
    if (root->parent != NULL) {
        if (getPositionRelativeToParent(root) == R)
            root->parent->right = pivot;
        else
            root->parent->left = pivot;
    }
    root->left = pivot->right;
    root->left->parent = root;
    pivot->right = root;
    pivot->parent = root->parent;
    root->parent = pivot;
    return pivot;
}


node *searchNodes(rbTree *tree, node *setNode, void *value) {
    if (tree->comparator(setNode->value, value) > 0) {
        if (setNode->left->value != NULL)
            return searchNodes(tree, setNode->left, value);
        else {
            return NULL;
        }

    } else if (tree->comparator(setNode->value, value) < 0) {
        if (setNode->right->value != NULL)
            return searchNodes(tree, setNode->right, value);
        else {
            return NULL;
        }

    } else if (tree->comparator(setNode->value, value) == 0) {
        return setNode;
    }
    perror("Unexpected error searching Nodes");
    exit(23);
}

int fixViolations(node *node) {
    struct node *grandparent;
    if (node->parent == NULL) {
        node->color = BLACK;
        return 1;
    }

    switch (checkViolation(node)) {
        case RIGHT_UNCLE_RED: {
            grandparent = node->parent->parent;
            grandparent->right->color = grandparent->right->color == BLACK ? RED : BLACK;
            grandparent->left->color = grandparent->left->color == BLACK ? RED : BLACK;
            //Check if it's a root node
            if (grandparent->parent != NULL)
                grandparent->color = grandparent->color == BLACK ? RED : BLACK;
            else
                grandparent->color = BLACK;
            fixViolations(grandparent);
            break;
        }
        case RIGHT_UNCLE_BLACK: {
            struct node *newRoot;
            grandparent = node->parent->parent;
            if (checkImbalanceCategoryRBT(node, L) == LL) {
                newRoot = rotateRightBT(grandparent);
            } else {
                rotateLeftBT(node->parent);
                newRoot = rotateRightBT(grandparent);
                newRoot->color = BLACK;
                newRoot->left->color = newRoot->right->color = RED;
            }
            newRoot->color = BLACK;
            newRoot->left->color = newRoot->right->color = RED;
            break;
        }
        case LEFT_UNCLE_RED: {
            grandparent = node->parent->parent;
            grandparent->right->color = grandparent->right->color == BLACK ? RED : BLACK;
            grandparent->left->color = grandparent->left->color == BLACK ? RED : BLACK;
            //Check if it's a root node
            if (grandparent->parent != NULL)
                grandparent->color = grandparent->color == BLACK ? RED : BLACK;
            else
                grandparent->color = BLACK;
            fixViolations(grandparent);
            break;
        }
        case LEFT_UNCLE_BLACK: {
            struct node *newRoot;
            grandparent = node->parent->parent;
            if (checkImbalanceCategoryRBT(node, R) == RR)
                newRoot = rotateLeftBT(grandparent);
            else {
                rotateRightBT(node->parent);
                newRoot = rotateLeftBT(grandparent);
            }
            newRoot->color = BLACK;
            newRoot->left->color = newRoot->right->color = RED;
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
 * 5 -> ROOT
 */
int checkViolation(node *node) {
    if (node->parent == NULL) {
        return ROOT;
    } else if (node->parent->color == BLACK)
        return NONE;
    else {
        if (getPositionRelativeToParent(node->parent) == R) {
            if (node->parent->parent->left->color == BLACK) {
                return LEFT_UNCLE_BLACK;
            } else {
                return LEFT_UNCLE_RED;
            }
        } else if (getPositionRelativeToParent(node->parent) == L) {
            if (node->parent->parent->right->color == BLACK) {
                return RIGHT_UNCLE_BLACK;
            } else {
                return RIGHT_UNCLE_RED;
            }
        }
        return NONE;
    }
}

/*
 * Checks for the imbalance category of the rbTree nodes.
 * params:
 *      subTreeRoot : node* <- node whose imbalance category is to be checked
 *      pos1 : int <- parent's position relative to grandparent( done in fixViolations)
 * returns:
 *      category : int <- can return: ( RR, RL, LL, LR )
 */
int checkImbalanceCategoryRBT(node *subtreeRoot, int pos1) {
    return pos1 == R ?
           getPositionRelativeToParent(subtreeRoot) == R ? RR : RL
                     :
           getPositionRelativeToParent(subtreeRoot) == L ? LL : LR;
}

void freeNode(node *node) {
    if (getPositionRelativeToParent(node) == R) {
        node->parent->right = NULL;
    } else {
        node->parent->left = NULL;
    }
    free(node->value);
    free(node);
}

void freeNodesBelow(node *node) {
    if (node->right != NULL)
        freeNodesBelow(node->right);
    if (node->left != NULL)
        freeNodesBelow(node->left);
    if (node->left == NULL && node->right == NULL) {
        freeNode(node);
    }
}

void freeRBTree(rbTree *tree) {
    freeNodesBelow(tree->root);
    free(tree);
}
