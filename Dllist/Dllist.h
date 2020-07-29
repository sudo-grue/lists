#ifndef DLLIST_H
#define DLLIST_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _DllistNode DllistNode;

struct _DllistNode {
    int data;
    DllistNode *next;   
    DllistNode *prev;   
};

typedef struct _Dllist {
    DllistNode *head;
} Dllist;

// Comparefunction
int dllistCompare(int a, int b);

// Doubly Linked List Methods to implement

/* dllistNew() creates a new doubly linked list
    Args:
        No arguments
    Return:
        Dllist * to a newly allocated doubly linked list.
*/
Dllist *dllistNew(void);

/* dllistAdd() adds to existing doubly linked list
    Args:
        Dllist * list : the dllist* to add the element to
        int data     : the specific data element to add
    Return:
        bool: true on success, false on failure
*/
bool dllistAdd(Dllist *list, int data);

/* dllistFind() searches a doubly linked list for the first occurance of a given value
    Args:
        Dllist * list : the Dllist* to find the element in
        int data     : the specific data element to find
    Return:
        DllistNode* of the found node. null if node not found.
*/
DllistNode *dllistFind(Dllist *list, int data);

/* dllistAddAfter() Adds item and data after specified value
    Args:
        Dllist * list : the Dllist* to add to
        int data     : the data to place in list
        int after    : the data to place this node after
    Return:
        True if node was placed in list, False if didn't find after or error
*/
bool dllistAddAfter(Dllist *list, int data, int after);

/* dllistAddBefore() Adds item and data after specified value
    Args:
        Dllist * list : the Dllist* to add to
        int data     : the data to place in list
        int after    : the data to place this node after
    Return:
        True if node was placed in list, False if didn't find before or error
*/
bool dllistAddBefore(Dllist *list, int data, int before);

/* dllistSort() sort a linked list in place in
                ascending/aplhanumerical order (i.e.: 1 - 10)
    Hint: It's methodically easier to move the data between nodes
    Args:
        Dllist *list : Dllist * to check
        Compare *funcptr : Function that can compare the data of two nodes
    Return:
        bool : true on success, false on empty lists or no lists
*/
bool dllistSort(Dllist *l, int (*Compare) (int, int));

/* dllistRmHead() removes only the head of a doubly linked list
    Args:
        Dllist * list : the Dllist* to remove the head from
    Return:
        DllistNode* of the removed head. null if list is empty.
*/
DllistNode *dllistRmHead(Dllist *list);

/* dllistRm() removes from existing doubly linked list
    Args:
        Dllist * list : the Dllist* to remove the element from
        int data     : the specific data element to remove
    Return:
        DllistNode* of the removed node. null if node not found.
*/
DllistNode *dllistRm(Dllist *list, int data);

/* dllistDestroy() destroys a doubly linked list
    Args:
        Dllist *list : Dllist * to destroy
    Return:
        bool : true on success, false of failure
*/
bool dllistDestroy(Dllist *list);

#endif
