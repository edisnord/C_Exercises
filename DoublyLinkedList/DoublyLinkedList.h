// DoublyLinkedList.h : Include file for standard system include files,
// or project specific include files.

#ifndef DOUBLY_LIST
#define DOUBLY_LIST

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct DoublyLinkedNode {
	struct DoublyLinkedNode* prev;
	struct DoublyLinkedNode* next;
	char* value;
} DoublyLinkedNode;

typedef struct DoublyLinkedList {
	DoublyLinkedNode* first;
	DoublyLinkedNode* last;
} DoublyLinkedList;

int nodeExists(DoublyLinkedList* list, DoublyLinkedNode* node);
int listLength(DoublyLinkedList* list);
DoublyLinkedNode getElement(int index, DoublyLinkedList* list);
void addBefore(DoublyLinkedList* list, DoublyLinkedNode* node, DoublyLinkedNode* newNode);
void addAfter(DoublyLinkedList* list, DoublyLinkedNode* node, DoublyLinkedNode* newNode);
void deleteNode(DoublyLinkedList* list, DoublyLinkedNode* node) ;

#endif