// DataStructures.cpp : Defines the entry point for the application.
//

#include "DoublyLinkedList.h"


int nodeExists(DoublyLinkedList* list, DoublyLinkedNode* node) {
	DoublyLinkedNode* currNode = list->first;
	for (int i = 0; currNode != list->last; i++)
	{
		if (currNode == node) return 1;
		currNode = currNode->next;
	}
	if (currNode == node) return 1;
	return 0;
}

int listLength(DoublyLinkedList* list) {
	DoublyLinkedNode* currNode = list->first;
	int i;
	for (i = 0; currNode != list->last; i++)
	{
		currNode = currNode->next;
	}
	return i + 1;
}

DoublyLinkedNode getElement(int index, DoublyLinkedList* list) {

	DoublyLinkedNode node;

	if (list != NULL) {
		if (list->first != NULL) {
			node = *(list->first);
		}
		else {
			node.next = NULL;
			node.prev = NULL;
			strcpy(node.value, "NO VALUE EXISTS");
		}

		for (int i = 0; i < index; i++)
		{
			if (node.next != NULL) {
				if (node.next == list->last && index != i+1) {
					printf("List out of bounds");
					exit(127);
					break;
				}
				node = *node.next;
			}

		}
		return node;
	}
}

void addBefore(DoublyLinkedList* list, DoublyLinkedNode* node, DoublyLinkedNode* newNode) {
	int isFirst = 0;
	if (list->first == NULL) {
		list->first = newNode;
		list->last = newNode;
		return;
	}
	else if (list->first == node) {
		isFirst = 1;
		list->first = newNode;
	}

	if (nodeExists(list, node)) {
		DoublyLinkedNode* prevNode = node->prev;
		node->prev = newNode;
		newNode->next = node;
		newNode->prev = prevNode;
		if(!isFirst)
		prevNode->next = newNode;
	}
	else {
		printf("%s", "Node you wish to insertSet element behind of doesn't exist");
	}
}

void addAfter(DoublyLinkedList* list, DoublyLinkedNode* node, DoublyLinkedNode* newNode) {
	int isLast = 0;
	if (list->first == NULL) {
		list->first = newNode;
		list->last = newNode;
		return;
	}
	else if (list->last == node) {
		isLast = 1;
		list->last = newNode;
	}

	if (nodeExists(list, node)) {
		
		DoublyLinkedNode* nextNode = node->next;
		node->next = newNode;
		newNode->prev = node;
		newNode->next = nextNode;
		if(!isLast){
			nextNode->next = newNode;
		}

	}
	else {
		printf("%s", "Node you wish to insertSet element after doesn't exist");
	}
}

void deleteNode(DoublyLinkedList* list, DoublyLinkedNode* node) {
	if (node->prev == NULL)
		list->first = node->next;
	else node->prev->next = node->next;
	if (node->next == NULL)
		list->last = node->prev;
	else node->next->prev = node->prev;

}

