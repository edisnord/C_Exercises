// DataStructures.h : Include file for standard system include files,
// or project specific include files.

#ifndef DOUBLY_LIST
#define DOUBLY_LIST
#define _GNU_SOURCE

#include <stdio.h>
#include "stdbool.h"
#include "string.h"
#include <stdlib.h>

#ifndef CMP
#define CMP
typedef int (*comparator)(const void *, const void *);
#endif

typedef struct DoublyLinkedNode DoublyLinkedNode;

typedef struct DoublyLinkedList DoublyLinkedList;

DoublyLinkedList * newDLL(size_t sizeOf, comparator comparator);
void appendDLL(DoublyLinkedList* list, void* value, int len);
bool existsDLL(DoublyLinkedList* list, void* value);
void removeDLL(DoublyLinkedList* list, int index);

#endif