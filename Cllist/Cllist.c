#include "Cllist.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Circularly Linked List Methods to implement

int cllistCompare(int a, int b)
{
	return a <= b;
}

bool cllistSort(Cllist * list, int (*Compare) (int, int))
{
	if (!list || !list->head) {
		return false;
	}
	CllistNode *node = list->head;

	while (node->next != list->head) {
		if (!Compare(node->data, node->next->data)) {
			node->data ^= node->next->data;
			node->next->data ^= node->data;
			node->data ^= node->next->data;
			node = list->head;
		} else {
			node = node->next;
		}
	}
	return true;
}

bool cllistInsertAfter(Cllist * list, int data, int after)
{
	CllistNode *node = cllistFind(list, after);
	if (!node) {
		return false;
	}
	CllistNode *newnode = malloc(sizeof(*newnode));
	if (!newnode) {
		return false;
	}

	newnode->data = data;
	newnode->next = node->next;
	node->next = newnode;
	if (list->tail == node) {
		list->tail = newnode;
	}
	return true;
}

Cllist *cllistNew(void)
{
	Cllist *cll = malloc(sizeof(*cll));
	if (cll) {
		cll->head = NULL;
		cll->tail = NULL;
	}
	return cll;
}

bool cllistAdd(Cllist * list, int data)
{
	if (!list) {
		return false;
	}
	CllistNode *node = malloc(sizeof(*node));
	if (!node) {
		return false;
	}
	if (list->tail) {
		list->tail->next = node;
		list->tail = node;
	} else {
		list->head = node;
		list->tail = node;
	}
	node->data = data;
	node->next = list->head;

	return true;
}

CllistNode *cllistFind(Cllist * list, int data)
{
	if (!list || !list->head) {
		return NULL;
	}
	CllistNode *node = list->head;
	do {
		if (node->data == data) {
			return node;
		}
		node = node->next;
	} while (node != list->head);
	return NULL;
}

CllistNode *cllistRmHead(Cllist * list)
{
	if (!list || !list->head) {
		return NULL;
	}
	CllistNode *head = list->head;
	if (head->next == head) {
		list->head = NULL;
		list->tail = NULL;
	} else {
		list->head = head->next;
		list->tail->next = list->head;
	}
	head->next = NULL;
	return head;
}

CllistNode *cllistRmTail(Cllist * list)
{
	if (!list || !list->head) {
		return NULL;
	}
	CllistNode *node = list->head;
	while (node->next != list->tail) {
		node = node->next;
	}
	CllistNode *tail = node->next;
	tail->next = NULL;
	if (tail == node) {
		list->head = NULL;
		list->tail = NULL;
	} else {
		node->next = list->head;
		list->tail = node;
	}
	return tail;
}

CllistNode *cllistRm(Cllist * list, int data)
{
	if (!list || !list->head) {
		return NULL;
	}
	// Special handling for head or single element
	if (list->head->data == data) {
		return cllistRmHead(list);
	} else if (list->head == list->tail) {
		return NULL;
	}
	// Fast forward until the next node matches or we reach tail
	CllistNode *node = list->head;
	while (node != list->tail) {
		if (node->next->data == data) {
			break;
		}
		node = node->next;
	}
	// Special handling for tail or not found
	if (node == list->tail) {
		return NULL;
	} else if (node->next == list->tail) {
		return cllistRmTail(list);
	}
	// Every normal case not already handled
	CllistNode *next = node->next;
	node->next = next->next;
	next->next = NULL;
	return next;
}

bool cllistDestroy(Cllist * list)
{
	if (!list) {
		return false;
	}
	CllistNode *temp = list->head;
	while (temp != list->tail) {
		CllistNode *prev = temp;
		temp = temp->next;
		free(prev);
	}
	free(temp);
	free(list);
	return true;
}

bool cllistIsCircular(Cllist * list)
{
	if (!list || !list->head) {
		return false;
	}
	CllistNode *node = list->head->next;
	while (node != list->head && node != NULL) {
		node = node->next;
	}
	if (node == list->head) {
		return true;
	}
	return false;
}
