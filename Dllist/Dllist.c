#include "Dllist.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Doubly Linked List Methods to implement

int dllistCompare(int a, int b)
{
	return a <= b;
}

bool dllistSort(Dllist *list, int (*Compare) (int, int))
{
	if (!list || !list->head) {
		return false;
	}

	DllistNode *node = list->head;

	while (node->next) {
		if (!Compare(node->data, node->next->data)) {
			node->data ^= node->next->data;
			node->next->data ^= node->data;
			node->data ^= node->next->data;
			if (node->prev) {
				node = node->prev;
			} else {
				node = node->next;
			}
		} else {
			node = node->next;
		}
	}
	return true;
}

bool dllistAddAfter(Dllist *list, int data, int after)
{
	DllistNode *node = dllistFind(list, after);
	if (!node) {
		return false;
	}
	DllistNode *newnode = malloc(sizeof(*newnode));
	if (!newnode) {
		return false;
	}

	newnode->next = node->next;
	if (newnode->next) {
		newnode->next->prev = newnode;
	}
	node->next = newnode;
	newnode->prev = node;
	newnode->data = data;

	return true;
}

bool dllistAddBefore(Dllist *list, int data, int before)
{
	DllistNode *node = dllistFind(list, before);
	if (!node) {
		return false;
	}
	DllistNode *newnode = malloc(sizeof(*newnode));
	if (!newnode) {
		return false;
	}

	newnode->prev = node->prev;
	newnode->next = node;
	node->prev = newnode;
	newnode->data = data;
	if (newnode->prev) {
		newnode->prev->next = newnode;
	} else {
		list->head = newnode;
	}
	return true;

}

Dllist *dllistNew(void)
{
        Dllist *dll = malloc(sizeof(*dll));
        if (dll) {
                dll->head = NULL;
        }
        return dll;
}

bool dllistAdd(Dllist *list, int data)
{
        if (!list) {
                return false;
        }
        DllistNode *node = malloc(sizeof(*node));
        if (!node) {
                return false;
        }
        node->next = list->head;
        if (list->head) {
                list->head->prev = node;
        }
        list->head = node;
        node->prev = NULL;
        node->data = data;
        return true;
}

DllistNode *dllistFind(Dllist *list, int data)
{
        if (!list) {
                return NULL;
        }
        DllistNode *node = list->head;
        while (node != NULL) {
                if (node->data == data) {
                        break;
                }
                node = node->next;
        }
        return node;
}

DllistNode *dllistRmHead(Dllist *list)
{
        if (!list) {
                return NULL;
        }
        DllistNode *node = list->head;
        if (node) {
                list->head = node->next;
                if (list->head) {
                        list->head->prev = NULL;
                }
                node->next = NULL;
        }
        return node;
}

DllistNode *dllistRm(Dllist *list, int data)
{
        if (!list || !list->head) {
                return NULL;
        }
        DllistNode *node = list->head;
        if (node->data == data) {
                return dllistRmHead(list);
        }
        DllistNode *next = node->next;
        while (next != NULL) {
                if (next->data == data) {
                        break;
                }
                node = next;
                next = next->next;
        }
        if (next) {
                node->next = next->next;
                if (next->next) {
                        next->next->prev = node;
                }
                next->prev = NULL;
                next->next = NULL;
        }
        return next;
}

bool dllistDestroy(Dllist * list)
{
        if (!list) {
                return false;
        }
        DllistNode *temp = list->head;
        while (temp != NULL) {
                DllistNode *prev = temp;
                temp = temp->next;
                free(prev);
        }
        free(list);
        return true;
}
