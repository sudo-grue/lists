#ifndef LLIST_H
#define LLIST_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _LlistNode LlistNode;

struct _LlistNode {
    int data;
    LlistNode *next;   
};

typedef struct _Llist {
    LlistNode *head;
} Llist;

// Comparefunction
int llistCompare(int a, int b);


/* llistNew() creates a new linked list
    Args:
        No arguments
    Return:
        Llist * to a newly allocated linked list.
*/
Llist *llistNew(void);

/* llistAdd() adds to existing linked list
    Args:
        Llist * list : the llist* to add the element to
        int data     : the specific data element to add
    Return:
        bool: true on success, false on failure
*/
bool llistAdd(Llist *list, int data);

/* llistFind() searches a linked list for the first occurance of a given value
    Args:
        Llist * list : the llist* to find the element in
        int data     : the specific data element to find
    Return:
        ListNode* of the found node. null if node not found.
*/
LlistNode *llistFind(Llist *list, int data);

/* llistSort() sort a linked list in place in
                ascending/aplhanumerical order (i.e.: 1 - 10)
    Hint: It's methodically easier to move the data between nodes
          than to shuffle the nodes around.
    Args:
        Llist *list : Llist * to check
        Compare *funcptr : Function that can compare the data of two nodes
    Return:
        bool : true on success, false on empty lists or no lists
*/
bool llistSort(Llist *l, int (*Compare) (int, int));

/* llistRmHead() removes only the head of a linked list
    Args:
        Llist * list : the Llist* to remove the head from
    Return:
        ListNode* of the removed head. null if list is empty.
*/
LlistNode *llistRmHead(Llist *list);

/* llistRm() removes from existing linked list
    Args:
        Llist * list : the Llist* to remove the element from
        int data     : the specific data element to remove
    Return:
        ListNode* of the removed node. null if node not found.
*/
LlistNode *llistRm(Llist *list, int data);


/* llistAddAfter() Adds item and data after specified value
    Args:
        Llist * list : the Llist* to add to
        int data     : the data to place in list
        int after    : the data to place this node after
    Return:
        True if node was placed in list, False if didn't find after
*/
bool llistAddAfter(Llist *l, int data, int after);

/* llistDestroy() destroys a linked list
    Args:
        Llist *list : Llist * to destroy
    Return:
        bool : true on success, false of failure
*/
bool llistDestroy(Llist *list);

#endif
