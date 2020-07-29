#include <CUnit/CUnit.h>

#include "../Llist/Llist.h"
#include "Common.h"

static Llist *llist;

// Helper Functions
static void printLlist(Llist *l)
{
    if (!l)
        return;

    printf(ANSI_COLOR_CYAN);
    LlistNode *tmp = l->head;
    printf("\tHead-> {");

    int nodeCount = 0;
    while(tmp)
    {
        printf("%d", tmp->data);
        ++nodeCount;
        if (tmp->next)
            printf(", ");
        tmp = tmp->next;
    }
    if (!l->head)
        printf(" NULL ");
    printf("}\n\n");
    printf("\t");
    printf("Node Count = %d\n", nodeCount);
    printf(ANSI_COLOR_YELLOW);
}

static LlistNode *findList(Llist *l, int data)
{
    if (!l) {
        return NULL;
    }
    LlistNode *tmp = l->head;
    while (tmp) {
        if (tmp->data == data) {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}


// Testing suite setup and teardown
static void llistSetup(void)
{
    printf(ANSI_COLOR_GREEN);
    puts("\n\tSETUP::Calling llistNew()");
    llist = llistNew();
    printf(ANSI_COLOR_YELLOW);
}

static void llistTeardown(void)
{
    printf(ANSI_COLOR_GREEN);
    puts("\n\tSETUP::Calling llistDestroy()");
    llistDestroy(llist);
    printf(ANSI_COLOR_RESET "\n");
}


// Testing items
static void CreateNew(void)
{
    printf("\n\tCreating a new list...");
    Llist *new = llistNew();
    CU_ASSERT_PTR_NOT_NULL(new);
    if (new) {
        free(new);
    }
}

static void EmptyList(void)
{
    printf("\n\tIs the head empty?\n");
    if (llist) {
        CU_ASSERT_PTR_NULL(llist->head);
    }
}

static void AddOneNull(void)
{
    Llist *tmp = NULL;
    printf("\n\n\tAdding 1 node to NULL list with value 25.\n");
    CU_ASSERT_FALSE(llistAdd(tmp, 25));
}

static void AddOne(void)
{
    printf("\n\n\tAdding 1 node to list with value 100.\n");
    CU_ASSERT_TRUE(llistAdd(llist, 100));
    printLlist(llist);
    printf("\n\tDoes the head match node, does the node point to NULL?\n");
    if (llist) {
        CU_ASSERT_EQUAL(llist->head->data, 100);
        CU_ASSERT_PTR_NULL(llist->head->next);
    }
}

static void AddFive(void)
{
    printf("\n\n\tAdding values 1 through 5...\n");
    for (int x = 1; x < 6; ++x) {
        CU_ASSERT_TRUE(llistAdd(llist, x));
    }
    printLlist(llist);
    puts("\tTesting list starts at 5 and goes to 1...");
    int count = 6;
    if (llist) {
        LlistNode *tmp = llist->head;
        while (tmp) {
            CU_ASSERT_EQUAL(tmp->data, --count);
            tmp = tmp->next;
        }
    }
}

static void FindOne(void)
{
    printf("\n\n\tAdding values 1 through 10...\n");
    for (int x = 1; x < 11; ++x) {
        llistAdd(llist, x);
    }
    printLlist(llist);

    LlistNode *test = findList(llist, 5);
    printf("\tLooking for 5...Address: %p\n", &test);
    LlistNode *user = llistFind(llist, 5);
    if (llist) {
        printf("\tUser node data: %d - User node address: %p\n", user->data, &user);
        printf("\tTest node data: %d - Test node address: %p\n", test->data, &test);
        CU_ASSERT_PTR_EQUAL(test, user);
        CU_ASSERT_EQUAL(test->data, user->data);
    }
}

static void FindOneNull(void)
{
    Llist *tmp = NULL;
    printf("\n\n\tFinding 2 in NULL list.\n");
    LlistNode *user = llistFind(tmp, 2);
    if (!user) {
        puts("\tNode pointer is NULL");
    }
    CU_ASSERT_PTR_NULL(user);
}

static void FindMissing(void)
{
    printf("\n\n\tAdding values 1 and 2...\n");
    for (int x = 1; x < 3; ++x) {
        llistAdd(llist, x);
    }
    printf("\n\n\tFinding 3 in list.\n");
    LlistNode *user = llistFind(llist, 3);
    if (!user) {
        puts("\tNode pointer is NULL");
    }
    CU_ASSERT_PTR_NULL(user);
}

static void FindFirstOne(void)
{
    printf("\n\n\tAdding values 1 through 5 with another 2...\n");
    for (int x = 1; x < 6; ++x) {
        llistAdd(llist, x);
    }
    llistAdd(llist, 2);
    printLlist(llist);

    if (llist) {
        LlistNode *test = findList(llist, 2);
        printf("\tLooking for 5...Address: %p\n", &test);
        LlistNode *user = llistFind(llist, 2);
        printf("\tUser node data: %d - User node address: %p\n", user->data, &user);
        printf("\tTest node data: %d - Test node address: %p\n", test->data, &test);
        CU_ASSERT_PTR_EQUAL(test, user);
        CU_ASSERT_EQUAL(test->data, user->data);
    }
}

static void SortNull(void)
{
    Llist *new = NULL;
    puts("\n\n\tSorting a NULL list..");
    CU_ASSERT_FALSE(llistSort(new, llistCompare));
}

static void SortEmpty(void)
{
    Llist *new = llistNew();
    puts("\n\n\tSorting an Empty list..");
    CU_ASSERT_FALSE(llistSort(new, llistCompare));
    free(new);
}

static void SortOne(void)
{
    puts("\n\n\tAdding 10 to the list...");
    CU_ASSERT_TRUE(llistAdd(llist, 10));
    printLlist(llist);
    CU_ASSERT_TRUE(llistSort(llist, llistCompare));
    printLlist(llist);
    puts("\tNothing should change...");
    if (llist) {
        CU_ASSERT_EQUAL(llist->head->data, 10);
        CU_ASSERT_PTR_NULL(llist->head->next);
    }
}


static void SortMany(void)
{
    printf("\n\n\tAdding values 1 through 11...\n");
    for (int x = 1; x < 11; ++x) {
        llistAdd(llist, x);
    }
    printLlist(llist);
    llistSort(llist, llistCompare);
    puts("\tSorting list in ascending order...");
    if (llist) {
        LlistNode *tmp = llist->head;
        int check = 1;
        while (tmp) {
            printf("\tChecking Node %2d - Value: %2d\n", check, tmp->data);
            CU_ASSERT_EQUAL(tmp->data, check);
            ++check;
            tmp = tmp->next;
        }
    }
}

static void RemoveHeadNull(void)
{
    Llist *tmp = NULL;
    puts("\n\n\tRemoving head from NULL list..");
    CU_ASSERT_PTR_NULL(llistRmHead(tmp));
}

static void RemoveHeadEmpty(void)
{
    Llist *tmp = llistNew();
    puts("\n\n\tRemoving head from Empty list..");
    CU_ASSERT_PTR_NULL(llistRmHead(tmp));
    free(tmp);
}

static void RemoveHead(void)
{
    printf("\n\n\tAdding values 1 through 10...\n");
    for (int x = 10; x > 0; --x) {
        llistAdd(llist, x);
    }
    printLlist(llist);
    if (llist) {
        LlistNode *tmp = llistRmHead(llist);
        CU_ASSERT_EQUAL(tmp->data, 1);
        free(tmp);
        CU_ASSERT_EQUAL(llist->head->data, 2);
        printLlist(llist);
    }
}

static void RemoveNull(void)
{
    Llist *tmp = NULL;
    puts("\n\n\tRemoving from NULL list..");
    CU_ASSERT_PTR_NULL(llistRmHead(tmp));
}

static void RemoveEmpty(void)
{
    Llist *tmp = llistNew();
    puts("\n\n\tRemoving from Empty list..");
    CU_ASSERT_PTR_NULL(llistRmHead(tmp));
    free(tmp);
}

static void RemoveOne(void)
{
    printf("\n\n\tAdding values 1 through 5...\n");
    for (int x = 1; x < 6; ++x) {
        CU_ASSERT_TRUE(llistAdd(llist, x));
    }
    printLlist(llist);
    puts("\n\tRemoving 1 and checking list til final node->next...\n");
    if (llist) {
        LlistNode *tmp = llistRm(llist, 1);
        CU_ASSERT_EQUAL(tmp->data, 1);
        free(tmp);
        tmp = llist->head;
        int count = 0;
        while (tmp) {
            ++count;
            tmp = tmp->next;
        }
        CU_ASSERT_EQUAL(count, 4);
        printLlist(llist);
    }
}

static void RemoveTwo(void)
{
    printf("\n\n\tAdding values 1 through 5...\n");
    for (int x = 1; x < 6; ++x) {
        CU_ASSERT_TRUE(llistAdd(llist, x));
    }
    printLlist(llist);
    puts("\n\tRemoving 1 then 5 and checking list til final node->next...\n");
    if (llist) {
        LlistNode *tmp = llistRm(llist, 1);
        CU_ASSERT_EQUAL(tmp->data, 1);
        free(tmp);
        tmp = llistRm(llist, 5);
        CU_ASSERT_EQUAL(tmp->data, 5);
        free(tmp);
        tmp = llist->head;
        int count = 0;
        while (tmp) {
            ++count;
            tmp = tmp->next;
        }
        CU_ASSERT_EQUAL(count, 3);
        printLlist(llist);
    }
}

static void RemoveOneFromOne(void)
{
    printf("\n\n\tAdding value 1...\n");
    CU_ASSERT_TRUE(llistAdd(llist, 1));
    printLlist(llist);
    puts("\tRemoving value 1 and validating list...");
    if (llist) {
        LlistNode *tmp = llistRm(llist, 1);
        CU_ASSERT_EQUAL(tmp->data, 1);
        free(tmp);
        CU_ASSERT_PTR_NULL(llist->head);
        printLlist(llist);
    }
}

static void InsertAfterNull(void)
{
    Llist *tmp = NULL;
    puts("\n\n\tInserting 1 after 10 in NULL list..");
    CU_ASSERT_FALSE(llistAddAfter(tmp, 1, 10));
}

static void InsertAfterEmpty(void)
{
    Llist *tmp = llistNew();
    puts("\n\n\tInserting 1 after 10 in Empty list..");
    CU_ASSERT_FALSE(llistAddAfter(tmp, 1, 10));
    free(tmp);
}

static void InsertAfterOne(void)
{
    printf("\n\n\tAdding values 1 through 5...\n");
    for (int x = 1; x < 6; ++x) {
        CU_ASSERT_TRUE(llistAdd(llist, x));
    }
    printLlist(llist);
    puts("\tInserting 10 after 5...");
    CU_ASSERT_TRUE(llistAddAfter(llist, 10, 1));
    printLlist(llist);
    if (llist) {
        LlistNode *tmp = findList(llist, 10);
        CU_ASSERT_EQUAL(tmp->data, 10);
        CU_ASSERT_PTR_NULL(tmp->next);
    }
}

static void InsertAfterTwo(void)
{
    printf("\n\n\tAdding values 1 through 5...\n");
    for (int x = 1; x < 6; ++x) {
        CU_ASSERT_TRUE(llistAdd(llist, x));
    }
    printLlist(llist);
    puts("\tInserting 10 after 3...");
    CU_ASSERT_TRUE(llistAddAfter(llist, 10, 3));
    puts("\tInserting 20 after 10...");
    CU_ASSERT_TRUE(llistAddAfter(llist, 20, 10));

    puts("\tChecking that 10 and 20 are in the right spots...");
    if (llist) {
        LlistNode *tmp = llist->head;
        int count = 0;
        while (tmp) {
            ++count;
            if (tmp->data == 10 && count == 4) {
                printf("\tFound 10 in spot %d.\n", count);
                CU_PASS();
            } else if (tmp->data == 10) {
                printf("\tFound 10 in spot %d.\n", count);
                CU_FAIL("Wrong index for insertion.");
            }
            if (tmp->data == 20 && count == 5) {
                printf("\tFound 20 in spot %d.\n", count);
                CU_PASS();
            }  else if (tmp->data == 20) {
                printf("\tFound 20 in spot %d.\n", count);
                CU_FAIL("Wrong index for insertion.");
            }
            tmp = tmp->next;
        }
        printLlist(llist);
    }
}



static CU_TestInfo listTests[] = {
    // Name, functionThatRunsTest
    { "NewList", CreateNew },
    { "EmptyList", EmptyList },
    { "Add one to NULL list", AddOneNull },
    { "Add one to list", AddOne },
    { "Add five to list", AddFive },
    { "Find 1 number in list", FindOne },
    { "Find 1 number in NULL list", FindOneNull },
    { "Find number not in list", FindMissing },
    { "Find first iteration of number", FindFirstOne },
    { "Sort NULL list", SortNull },
    { "Sort Empty list", SortEmpty },
    { "Sort one item", SortOne },
    { "Sort many items", SortMany },
    { "Remove list head from NULL", RemoveHeadNull },
    { "Remove list head from Empty", RemoveHeadEmpty },
    { "Remove list head", RemoveHead },
    { "Remove one from NULL list", RemoveNull },
    { "Remove one from Empty list", RemoveEmpty },
    { "Remove one from list", RemoveOne },
    { "Remove two from list", RemoveTwo },
    { "Remove one from list of one", RemoveOneFromOne },
    { "Insert After with NULL list", InsertAfterNull },
    { "Insert After with Empty list", InsertAfterEmpty },
    { "Insert one value at end", InsertAfterOne },
    { "Insert two values after", InsertAfterTwo },
    CU_TEST_INFO_NULL
};

CU_SuiteInfo llistSuite = {
    // Name, suiteSetup, suiteTeardown, testSetup, testTeardown, arrayOfTests
    "Linked-List Tests",
    NULL,
    NULL,
    llistSetup,
    llistTeardown,
    listTests
};
