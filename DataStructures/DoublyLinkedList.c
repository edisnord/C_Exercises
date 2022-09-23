// DataStructures.cpp : Defines the entry point for the application.
//

#include "DoublyLinkedList.h"

typedef struct DoublyLinkedNode {
    struct DoublyLinkedNode *prev;
    struct DoublyLinkedNode *next;
    void *value;
} DoublyLinkedNode;

typedef struct DoublyLinkedList {
    DoublyLinkedNode *first;
    DoublyLinkedNode *last;
    comparator equals;
    size_t elementSize;
    int length;
} DoublyLinkedList;

int nodeExists(DoublyLinkedList *list, DoublyLinkedNode *node);

int listLength(DoublyLinkedList *list);

DoublyLinkedNode *getElement(int index, DoublyLinkedList *list);

void addBefore(DoublyLinkedList *list, int index, DoublyLinkedNode *newNode);

void addAfter(DoublyLinkedList *list, int index, DoublyLinkedNode *newNode);

void deleteNode(DoublyLinkedList *list, DoublyLinkedNode *node);

DoublyLinkedNode *createNode(DoublyLinkedList *list, void *val, int len) {
    DoublyLinkedNode *node = malloc(sizeof(struct DoublyLinkedNode));
    void *value = malloc(list->elementSize * len);
    memcpy(value, val, list->elementSize * len);
    *node = (struct DoublyLinkedNode) {NULL, NULL, value};
    return node;
}

DoublyLinkedList *newDLL(size_t sizeOf, comparator comparator) {
    DoublyLinkedList *list = malloc(sizeof(DoublyLinkedList));
    *list = (struct DoublyLinkedList) {NULL, NULL, comparator, sizeOf, 0};
    return list;
}

int lengthDLL(DoublyLinkedList* list){
    return list->length;
}

void appendDLL(DoublyLinkedList *list, void *value, size_t len) {
    DoublyLinkedNode *node = createNode(list, value, len);
    if (list->last == NULL) {
        list->first = node;
        list->last = node;
        list->length++;
        return;
    }
    addAfter(list, listLength(list) - 1, node);
    list->length++;
}

bool existsDLL(DoublyLinkedList *list, void *value) {
    if (list->equals == NULL) {
        printf("existsDLL: No comparator has been given for these values, can't check");
        return false;
    }
    DoublyLinkedNode *currNode = list->first;
    for (int i = 0; currNode != list->last; i++) {
        if (list->equals(currNode->value, value) == 0) return true;
        currNode = currNode->next;
    }
    if (list->equals(currNode->value, value)) return true;
    return false;
}

void removeDLL(DoublyLinkedList *list, int index) {
    if (index < 0 || index >= listLength(list)) {
        char *error;
        asprintf(&error, "Index %d out of bounds for Doubly Linked List", index);
        perror(error);
        exit(1);
    }
    deleteNode(list, getElement(index, list));
    list->length--;
}

void* getDLL(DoublyLinkedList* list, int index){
    DoublyLinkedNode *currNode = list->first;
    for (int i = 0; i < index; i++) {
        currNode = currNode->next;
    }
    return currNode->value;
}

void freeDLL(DoublyLinkedList *list) {
    DoublyLinkedNode *currNode;
    for (currNode = list->last->prev; currNode->prev != NULL; currNode = currNode->prev) {
        deleteNode(list, currNode->next);
    }
    deleteNode(list, currNode);
    free(list);
}

int nodeExists(DoublyLinkedList *list, DoublyLinkedNode *node) {
    DoublyLinkedNode *currNode = list->first;
    for (int i = 0; currNode != list->last; i++) {
        if (currNode == node) return 1;
        currNode = currNode->next;
    }
    if (currNode == node) return 1;
    return 0;
}


int listLength(DoublyLinkedList *list) {
    DoublyLinkedNode *currNode = list->first;
    int i;
    for (i = 0; currNode != list->last; i++) {
        currNode = currNode->next;
    }
    return i + 1;
}

DoublyLinkedNode *getElement(int index, DoublyLinkedList *list) {
    DoublyLinkedNode *nodePtr = NULL;
    if (list != NULL) {
        if (list->first == NULL) {
            return NULL;
        }

        nodePtr = list->first;

        for (int i = 0; i < index; i++) {
            if (nodePtr->next != NULL) {
                if ((nodePtr = nodePtr->next) == list->last && index != i + 1) {
                    return NULL;
                }
            }

        }
        return nodePtr;
    }
}

void addBefore(DoublyLinkedList *list, int index, DoublyLinkedNode *newNode) {
    DoublyLinkedNode *node = getElement(index, list);
    //Check if there are no nodes in tree
    if (list->first == NULL) {
        list->first = newNode;
        list->last = newNode;
        return;
    }
    //Perform insertion
    if (node != NULL) {
        newNode->next = node;
        newNode->prev = node->prev;
        if (node->prev != NULL) {
            node->prev->next = newNode;
        }
        node->prev = newNode;
        if (list->first == node)
            list->first = newNode;
    } else {
        printf("DoublyLinkedList: The node before which you wish to insert is not part of this list");
    }
}

void addAfter(DoublyLinkedList *list, int index, DoublyLinkedNode *newNode) {
    DoublyLinkedNode *node = getElement(index, list);
    if (list->first == NULL) {
        list->first = newNode;
        list->last = newNode;
        return;
    }

    if (node != NULL) {
        newNode->prev = node;
        newNode->next = node->next;
        if (node->next != NULL)
            node->next->prev = newNode;
        node->next = newNode;
        if (list->last == node)
            list->last = newNode;
    } else {
        printf("DoublyLinkedList: The node after which you wish to insert is not part of this list");
    }
}

void deleteNode(DoublyLinkedList *list, DoublyLinkedNode *node) {
    if (node->prev == NULL)
        list->first = node->next;
    else node->prev->next = node->next;
    if (node->next == NULL)
        list->last = node->prev;
    else node->next->prev = node->prev;
    free(node->value);
    free(node);
}

