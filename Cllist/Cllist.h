#ifndef CLLIST_H
#define CLLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _CllistNode CllistNode;

struct _CllistNode {
	int data;
	CllistNode *next;
};

typedef struct _Cllist {
	CllistNode *head;
	CllistNode *tail;
} Cllist;

// Compare function
int cllistCompare(int a, int b);

// Circularly Linked List Methods to implement

/* cllistNew() creates a new circularly linked list
    Args:
        No arguments
    Return:
        Cllist * to a newly allocated circularly linked list.
*/
Cllist *cllistNew(void);

/* cllistAdd() adds to existing circularly linked list
    (Use the tail pointer to add to the rear in O(1))
    Args:
        Cllist * list : the cllist* to add the element to
        int data     : the specific data element to add
    Return:
        bool: true on success, false on failure
*/
bool cllistAdd(Cllist *list, int data);

/* cllistFind() searches a circularly linked list for the first occurance of a given value
    Args:
        Cllist * list : the cllist* to find the element in
        int data     : the specific data element to find
    Return:
        CllistNode* of the found node. null if node not found.
*/
CllistNode *cllistFind(Cllist *list, int data);

/* cllistRmHead() removes only the head of a circularly linked list
    Args:
        Cllist * list : the cllist* to remove the head from
    Return:
        CllistNode* of the removed head. null if list is empty.
*/
CllistNode *cllistRmHead(Cllist *list);

/* cllistRmTail() removes only the tail of a circularly linked list
    Args:
        Cllist * list : the Cllist* to remove the tail from
    Return:
        CllistNode* of the removed tail. null if list is empty.
*/
CllistNode *cllistRmTail(Cllist *list);

/* cllistRm() removes from existing circularly linked list
    Args:
        Cllist * list : the cllist* to remove the element from
        int data     : the specific data element to remove
    Return:
        CllistNode* of the removed node. null if node not found.
*/
CllistNode *cllistRm(Cllist *list, int data);

/* cllistDestroy() destroys a circularly linked list
    Args:
        Cllist *list : cllist * to destroy
    Return:
        bool : true on success, false of failure
*/
bool cllistDestroy(Cllist *list);

/* cllistInsertAfter() data to insert after data point
    Args:
        Cllist *list : cllist * to check
        int data: value to add to list
        int after: data value to place after
    Return:
        bool : true on success, false on error or missing data value
*/
bool cllistInsertAfter(Cllist *list, int data, int after);

/* cllistSort() sort a linked list in place in
                ascending/aplhanumerical order (i.e.: 1 - 10)
    Hint: It's methodically easier to move the data between nodes
          than to shuffle the nodes around.
    Args:
        Cllist *list : cllist * to check
        Compare *funcptr : Function that can compare the data of two nodes
    Return:
        bool : true on success, false on empty lists or no lists
*/
bool cllistSort(Cllist *l, int (*Compare) (int, int));

#endif
