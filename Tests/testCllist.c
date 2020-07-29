#include <CUnit/CUnit.h>

#include "../Cllist/Cllist.h"
#include "Common.h"


static Cllist *cllist;

// Setup and destroy functions for suite
static void CllistSetup(void)
{
    printf(ANSI_COLOR_GREEN);
    puts("\n\tSETUP::Calling cllistNew()");
    cllist = cllistNew();
    printf(ANSI_COLOR_YELLOW);
}

static void CllistTeardown(void)
{
    printf(ANSI_COLOR_GREEN);
    puts("\n\tSETUP::Calling cllistDestroy()");
    cllistDestroy(cllist);
    printf(ANSI_COLOR_RESET "\n");
}

// Helper function to search
static CllistNode *CllistTests_searchList(Cllist *list, int data)
{
    if (!list) {
        return NULL;
    }
    if (list->head == list->tail) {
        return list->head;
    }
    CllistNode *tmp = list->head;
    while (tmp->next != list->head) {
        if (data == tmp->data) {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}


// Print the Data
static void printCllistData(Cllist *cllist)
{
    if (!cllist)
        return;

    printf(ANSI_COLOR_CYAN);
    CllistNode *tmpNode = cllist->head;
    printf("\tHead-> {");

    int nodeCount = 0;
    while(tmpNode)
    {
        printf("%d", tmpNode->data);
        ++nodeCount;
        if (tmpNode->next == cllist->head)
        {
            break;
        }
        if (tmpNode)
            printf(", ");
        tmpNode = tmpNode->next;
    }
    if (!cllist->head)
        printf(" NULL ");
    printf("}\n\n");
    printf("\t");
    printf("Node Count = %d\n", nodeCount);
    printf(ANSI_COLOR_YELLOW);
}


// BEGIN TESTING
static void CreateNew(void)
{
    printf("\n\tCreating a new list...");
    Cllist *newList = cllistNew();
    CU_ASSERT_PTR_NOT_NULL(newList);
    if (newList) {
        free(newList);
    }
}

static void EmptyList(void)
{
    printf("\n\tIs the head empty?\n");
    if (cllist) {
        CU_ASSERT_PTR_NULL(cllist->head);
    }
}

static void AddOneEmpty(void)
{
    Cllist *tmp = NULL;
    printf("\n\n\tAdding 1 node to NULL list with value 100.\n");
    CU_ASSERT_FALSE(cllistAdd(tmp, 100));
}

static void AddOne(void)
{
    printf("\n\n\tAdding 1 node to list with value 100.\n");
    CU_ASSERT_TRUE(cllistAdd(cllist, 100));
    printCllistData(cllist);
    printf("\n\tDoes the head and tail match, does it point to itself?\n");
    if (cllist) {
        CU_ASSERT_EQUAL(cllist->head->data, 100);
        CU_ASSERT_EQUAL(cllist->tail->data, 100);
        CU_ASSERT_PTR_EQUAL(cllist->head, cllist->head->next);
    }
}

static void AddTen(void)
{
    printf("\n\n\tAdding values 1 through 10...\n");
    for (int x = 1; x < 11; ++x) {
        CU_ASSERT_TRUE(cllistAdd(cllist, x));
    }
    printCllistData(cllist);
    puts("\tTesting for head to be 1 and tail to be 10:");
    if (cllist) {
        printf("\t\tHead value: %d\n\t\tTail value: %d \n", cllist->head->data, cllist->tail->data);
        CU_ASSERT_EQUAL(cllist->head->data, 1);
        CU_ASSERT_EQUAL(cllist->tail->data, 10);
    }
}

static void FindOne(void)
{
    printf("\n\n\tAdding values 1 through 10...\n");
    for (int x = 1; x < 11; ++x) {
        cllistAdd(cllist, x);
    }
    printCllistData(cllist);

    if (cllist) {
        CllistNode *test = CllistTests_searchList(cllist, 5);
        printf("\tLooking for 5...Address: %p\n", &test);
        CllistNode *user = cllistFind(cllist, 5);
        printf("\tUser node data: %d - User node address: %p\n", user->data, &user);
        printf("\tTest node data: %d - Test node address: %p\n", test->data, &test);
        CU_ASSERT_PTR_EQUAL(test, user);
        CU_ASSERT_EQUAL(test->data, user->data);
    }
}

static void FindOneEmpty(void)
{
    Cllist *tmp = NULL;
    printf("\n\n\tFinding 2 in NULL list.\n");
    if (cllist) {
        CllistNode *user = cllistFind(tmp, 2);
        if (!user) {
            puts("\tNode pointer is NULL");
        }
        CU_ASSERT_PTR_NULL(user);
    }
}

static void FindMissing(void)
{
    printf("\n\n\tAdding values 1 and 2...\n");
    for (int x = 1; x < 3; ++x) {
        cllistAdd(cllist, x);
    }
    printf("\n\n\tFinding 3 in list.\n");
    if (cllist) {
        CllistNode *user = cllistFind(cllist, 3);
        if (!user) {
            puts("\tNode pointer is NULL");
        }
        CU_ASSERT_PTR_NULL(user);
    }
}

static void FindFirstOne(void)
{
    printf("\n\n\tAdding values 1 through 10 with another 2...\n");
    for (int x = 1; x < 11; ++x) {
        cllistAdd(cllist, x);
    }
    cllistAdd(cllist, 2);
    printCllistData(cllist);
    if (cllist) {
        CllistNode *test = CllistTests_searchList(cllist, 2);
        printf("\tLooking for 5...Address: %p\n", &test);
        CllistNode *user = cllistFind(cllist, 2);
        printf("\tUser node data: %d - User node address: %p\n", user->data, &user);
        printf("\tTest node data: %d - Test node address: %p\n", test->data, &test);
        CU_ASSERT_PTR_EQUAL(test, user);
        CU_ASSERT_EQUAL(test->data, user->data);
    }
}

static void SortOne(void)
{
    puts("\n\tAdding 10 to the list...");
    CU_ASSERT_TRUE(cllistAdd(cllist, 10));
    printCllistData(cllist);
    cllistSort(cllist, cllistCompare);
    printCllistData(cllist);
    puts("\tNothing should change...");
    if (cllist) {
        CU_ASSERT_PTR_EQUAL(cllist->head, cllist->tail);
    }
}

static void SortMany(void)
{
    printf("\n\n\tAdding values 10 down to 1...\n");
    for (int x = 10; x > 0; --x) {
        cllistAdd(cllist, x);
    }
    printCllistData(cllist);
    cllistSort(cllist, cllistCompare);
    puts("\tSorting list in ascending order...");

    if (cllist) {
        CllistNode *tmp = cllist->head;
        int check = 1;
        while (tmp) {
            printf("\tChecking Node %2d - Value: %2d\n", check, tmp->data);
            CU_ASSERT_EQUAL(tmp->data, check);
            ++check;
            if (tmp == cllist->tail) {
                break;
            }
            tmp = tmp->next;
        }
    }
}

static void SortNullList(void)
{
    Cllist *tmp = NULL;
    if (cllistSort(tmp, cllistCompare)) {
        CU_FAIL("Can't sort empty or NULL lists");
    } else {
        CU_PASS();
    }
}

static void SortEmptyList(void)
{
    Cllist *tmp = cllistNew();
    if (cllistSort(tmp, cllistCompare)) {
        CU_FAIL("Can't sort empty or NULL lists");
    } else {
        CU_PASS();
    }
    cllistDestroy(tmp);
}

static void RemoveHeadNull(void)
{
    Cllist *tmp = NULL;
    CU_ASSERT_PTR_NULL(cllistRmHead(tmp));
}

static void RemoveHeadEmpty(void)
{
    Cllist *tmp = cllistNew();
    CU_ASSERT_PTR_NULL(cllistRmHead(tmp));
    free(tmp);
}

static void RemoveHeadOne(void)
{
    puts("\n\tAdding 1 node value 10...");
    cllistAdd(cllist, 10);
    printCllistData(cllist);
    puts("\tRemoving 10\n\tChecking List head and tail are NULL...");
    if (cllist) {
        CllistNode *tmp = cllistRmHead(cllist);
        CU_ASSERT_EQUAL(tmp->data, 10);
        free(tmp);
        CU_ASSERT_PTR_NULL(cllist->head);
        CU_ASSERT_PTR_NULL(cllist->tail);
        printCllistData(cllist);
    }
}

static void RemoveHeadMany(void)
{
    printf("\n\n\tAdding values 1 through 10...\n");
    for (int x = 1; x < 11; ++x) {
        cllistAdd(cllist, x);
    }
    printCllistData(cllist);
    puts("\tRemoving 1\n\tChecking List head equal to value 2...");
    if (cllist) {
        CllistNode *tmp = cllistRmHead(cllist);
        CU_ASSERT_EQUAL(tmp->data, 1);
        free(tmp);
        CU_ASSERT_EQUAL(cllist->head->data, 2);
        puts("\tChecking tail points to new head...");
        printf("\tHead data: %d - @ %p tail->next @ %p\n", cllist->head->data, &cllist->head, &cllist->tail->next);
        if (cllist->tail->next != cllist->head) {
            CU_FAIL("Tail does not point to head");
        } else {
            CU_PASS();
        }
        printCllistData(cllist);
    }
}

static void RemoveTailNull(void)
{
    Cllist *tmp = NULL;
    CU_ASSERT_PTR_NULL(cllistRmTail(tmp));
}

static void RemoveTailEmpty(void)
{
    Cllist *tmp = cllistNew();
    CU_ASSERT_PTR_NULL(cllistRmTail(tmp));
    free(tmp);
}

static void RemoveTailOne(void)
{
    puts("\n\tAdding 1 node value 10...");
    cllistAdd(cllist, 10);
    printCllistData(cllist);
    puts("\tRemoving 10\n\tChecking List head and tail are NULL...");
    if (cllist) {
        CllistNode *tmp = cllistRmTail(cllist);
        CU_ASSERT_EQUAL(tmp->data, 10);
        free(tmp);
        CU_ASSERT_PTR_NULL(cllist->head);
        CU_ASSERT_PTR_NULL(cllist->tail);
        printCllistData(cllist);
    }
}

static void RemoveTailMany(void)
{
    printf("\n\n\tAdding values 1 through 10...\n");
    for (int x = 1; x < 11; ++x) {
        cllistAdd(cllist, x);
    }
    printCllistData(cllist);
    puts("\tRemoving 10\n\tChecking List tail equal to value 9...");
    if (cllist) {
        CllistNode *tmp = cllistRmTail(cllist);
        CU_ASSERT_EQUAL(tmp->data, 10);
        free(tmp);
        CU_ASSERT_EQUAL(cllist->tail->data, 9);
        puts("\tChecking tail points to new head...");
        printf("\tTail data: %d - tail->next @ %p Head @ %p\n",
            cllist->tail->data, &cllist->tail->next, &cllist->head);
        if (cllist->tail->next != cllist->head) {
            CU_FAIL("Tail does not point to head");
        } else {
            CU_PASS();
        }
        printCllistData(cllist);
    }
}

static void RemoveOne(void)
{
    puts("\n\tAdding 1 node value 10...");
    cllistAdd(cllist, 10);
    printCllistData(cllist);
    puts("\tRemoving 10\n\tChecking List head and tail are NULL...");
    if (cllist) {
        CllistNode *tmp = cllistRm(cllist, 10);
        CU_ASSERT_EQUAL(tmp->data, 10);
        free(tmp);
        CU_ASSERT_PTR_NULL(cllist->head);
        CU_ASSERT_PTR_NULL(cllist->tail);
        printCllistData(cllist);
    }
}

static void RemoveTwo(void)
{
    printf("\n\n\tAdding values 1 through 10...\n");
    for (int x = 1; x < 11; ++x) {
        cllistAdd(cllist, x);
    }
    printCllistData(cllist);
    puts("\tRemoving 1, 10");
    if (cllist) {
        CllistNode *tmp1 = cllistRm(cllist, 1);
        CllistNode *tmp2 = cllistRm(cllist, 10);
        CU_ASSERT_EQUAL(tmp1->data, 1);
        CU_ASSERT_EQUAL(tmp2->data, 10);
        free(tmp1);
        free(tmp2);
        CU_ASSERT_EQUAL(cllist->head->data, 2);
        CU_ASSERT_EQUAL(cllist->tail->data, 9);
        if (cllist->tail->next != cllist->head) {
            CU_FAIL("Tail does not point to head");
        } else {
            CU_PASS();
        }
        printCllistData(cllist);
    }
}

static void RemoveEmpty(void)
{
    Cllist *tmp = cllistNew();
    CU_ASSERT_PTR_NULL(cllistRm(tmp, 10));
    free(tmp);
}

static void RemoveNull(void)
{
    Cllist *tmp = NULL;
    CU_ASSERT_PTR_NULL(cllistRm(tmp, 10));
}

static void InsertAfterTail(void)
{
    printf("\n\n\tAdding values 1 through 5...\n");
    for (int x = 1; x < 6; ++x) {
        cllistAdd(cllist, x);
    }
    printCllistData(cllist);
    puts("\tInserting 6 after the tail...");
    
    CU_ASSERT_TRUE(cllistInsertAfter(cllist, 6, 5));
    if (cllist) {
        CU_ASSERT_EQUAL(cllist->tail->data, 6);
        CU_ASSERT_EQUAL(cllist->head->data, 1);
        if (cllist->tail->next != cllist->head) {
            CU_FAIL("Tail does not point to head");
        } else {
            CU_PASS();
        }
        printCllistData(cllist);
        printf("\tHead should be 1 - Head: %d\n\tTail should be 6 - Tail: %d\n",
                cllist->head->data, cllist->tail->data);
    }
}

static void InsertAfter(void)
{
    printf("\n\n\tAdding values 1 through 5...\n");
    for (int x = 1; x < 6; ++x) {
        cllistAdd(cllist, x);
    }
    printCllistData(cllist);
    puts("\tInserting 10 after the 1...");
    
    CU_ASSERT_TRUE(cllistInsertAfter(cllist, 10, 1));
    if (cllist) {
        CU_ASSERT_EQUAL(cllist->tail->data, 5);
        CU_ASSERT_EQUAL(cllist->head->next->data, 10);
        CU_ASSERT_EQUAL(cllist->head->data, 1);
        if (cllist->tail->next != cllist->head) {
            CU_FAIL("Tail does not point to head");
        } else {
            CU_PASS();
        }
        printCllistData(cllist);
    }
}

static CU_TestInfo listTests[] = {
    // Name, functionThatRunsTest
    { "NewList", CreateNew },
    { "Empty List", EmptyList },
    { "Adding to empty list", AddOneEmpty },
    { "Testing add one", AddOne },
    { "Testing add ten", AddTen },
    { "Finding one", FindOne },
    { "Finding in NULL list", FindOneEmpty },
    { "Finding missing value", FindMissing },
    { "Finding the first data point", FindFirstOne },
    { "Sorting one item", SortOne },
    { "Sorting many items", SortMany },
    { "Sorting NULL list", SortNullList },
    { "Sorting empty list", SortEmptyList },
    { "Removing head with Empty List", RemoveHeadEmpty },
    { "Removing head on NULL list", RemoveHeadNull },
    { "Removing head with only 1 item", RemoveHeadOne },
    { "Removing head with many items", RemoveHeadMany },
    { "Removing tail with Empty List", RemoveTailEmpty },
    { "Removing tail with NULL List", RemoveTailNull },
    { "Removing tail with only 1 items", RemoveTailOne },
    { "Removing tail with many items", RemoveTailMany },
    { "Removing one item", RemoveOne },
    { "Removing two items, from ends", RemoveTwo },
    { "Removing from Empty list", RemoveEmpty },
    { "Removing from NULL list", RemoveNull },
    { "Inserting after tail", InsertAfterTail },
    { "Inserting after", InsertAfter },
    CU_TEST_INFO_NULL
};

CU_SuiteInfo cllistSuite = {
    // Name, suiteSetup, suiteTeardown, testSetup, testTeardown, arrayOfTests
    "Circular Linked-list Tests",
    NULL,
    NULL,
    CllistSetup,
    CllistTeardown,
    listTests
};
