//
// Created by Edis Hasaj on 7/26/2022.
//

#include "set.h"

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
node *newTreeNode(char *val) {
    node *nodePtr = malloc(sizeof(node));
    if (nodePtr == NULL) {
        fprintf(stderr, "No more MALLOC space!");
    }
    strcpy(nodePtr->value = malloc(sizeof(char) * strlen(val)), val);
    nodePtr->parent = NULL;
    nodePtr->left = newNullNode(nodePtr);
    nodePtr->right = newNullNode(nodePtr);
    nodePtr->color = RED;
    return nodePtr;
}

int insertSet(set *set, char *val) {
    node *node = newTreeNode(val);
    if (set->root == NULL || set->height == 0) {
        node->color = BLACK;
        set->root = node;
        set->height++;
        return 1;
    }

    int assumedHeight;
    set->height = (assumedHeight = insertNodeBT(set->root, node)) > 0 ? assumedHeight : set->height;


    return set->height > 0 ? fixViolations(node) : 0;
}

int insertNodeBT(node *setNode, node *node) {
    if (strcmp(setNode->value, node->value) > 0) {
        if (setNode->left->value != NULL)
            return 1 + insertNodeBT(setNode->left, node);
        else {
            free(setNode->left);
            node->parent = setNode;
            setNode->left = node;
            return 1;
        }

    } else if (strcmp(setNode->value, node->value) < 0) {
        if (setNode->right->value != NULL)
            return 1 + insertNodeBT(setNode->right, node);
        else {
            free(setNode->right);
            node->parent = setNode;
            setNode->right = node;
            return 1;
        }

    } else if (strcmp(setNode->value, node->value) == 0) {
        return -1316134912;
    }

}

//Left rotation rooted at parameter node "root"
node *rotateLeftBT(node *root) {
    node *pivot = root->right;
    if (getPositionRelativeToParent(root) == R)
        root->parent->right = pivot;
    else
        root->parent->left = pivot;
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
    if (getPositionRelativeToParent(root) == R)
        root->parent->right = pivot;
    else
        root->parent->left = pivot;
    root->left = pivot->right;
    root->left->parent = root;
    pivot->right = root;
    pivot->parent = root->parent;
    root->parent = pivot;
    return pivot;
}

node *searchSet(node *setNode, char *string) {
    if (strcmp(setNode->value, string) > 0) {
        if (setNode->left->value != NULL)
            return searchSet(setNode->left, string);
        else {
            return NULL;
        }

    } else if (strcmp(setNode->value, string) < 0) {
        if (setNode->right->value != NULL)
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
    return NONE;
}

/*
 * Checks for the imbalance category of the tree nodes.
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