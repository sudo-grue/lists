#include "Llist.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Singularly Linked List Methods to implement
 */

int llistCompare(int a, int b)
{
	// = important to avoid zeroing out if they're equal
	return a <= b;
}


// This is not an insertion sort, but meets expectations of assignment (very
// inefficient)
bool llistSort(Llist *list, int (*Compare) (int, int))
{
        if (!list || !list->head) {
                return false;
        }

	LlistNode *node = list->head;

	while (node->next) {
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

Llist *llistNew(void)
{
        Llist *ll = malloc(sizeof(*ll));
        if (ll) {
                ll->head = NULL;
        }
        return ll;
}

bool llistAdd(Llist *list, int data)
{
        if (!list) {
                return false;
        }
        LlistNode *node = malloc(sizeof(*node));
        if (!node) {
                return false;
        }
        node->data = data;
        node->next = list->head;
        list->head = node;
        return true;
}

LlistNode *llistFind(Llist *list, int data)
{
        if (!list) {
                return NULL;
        }
        LlistNode *node = list->head;
        while (node != NULL) {
                if (node->data == data) {
                        break;
                }
                node = node->next;
        }
        return node;
}

LlistNode *llistRmHead(Llist *list)
{
        if (!list) {
                return NULL;
        }
        LlistNode *node = list->head;
        if (node) {
                list->head = node->next;
                node->next = NULL;
        }
        return node;
}

LlistNode *llistRm(Llist *list, int data)
{
        if (!list || !list->head) {
                return NULL;
        }
        LlistNode *node = list->head;
        if (node->data == data) {
                return llistRmHead(list);
        }
        LlistNode *next = node->next;
        while (next != NULL) {
                if (next->data == data) {
                        break;
                }
                node = next;
                next = next->next;
        }
        if (next) {
                node->next = next->next;
                next->next = NULL;
        }
        return next;
}

bool llistAddAfter(Llist *list, int data, int after)
{
	LlistNode *node = llistFind(list, after);
	if (!node) {
		return false;
	}

        LlistNode *new_node = malloc(sizeof(*new_node));
        if (!new_node) {
                return false;
        }

	new_node->data = data;
	new_node->next = node->next;
	node->next = new_node;

        return true;
}

bool llistDestroy(Llist *list)
{
        if (!list) {
                return false;
        }
        LlistNode *temp = list->head;
        while (temp != NULL) {
                LlistNode *prev = temp;
                temp = temp->next;
                free(prev);
        }
        free(list);
        return true;
}
