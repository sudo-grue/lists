#include <CUnit/CUnit.h>

#include "../Dllist/Dllist.h"
#include "Common.h"

static Dllist *dllist;

// Helper Functions
static void printDlist(Dllist *l)
{
    if (!l)
        return;

    printf(ANSI_COLOR_CYAN);
    DllistNode *tmp = l->head;
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

static DllistNode *findList(Dllist *l, int data)
{
    if (!l) {
        return NULL;
    }
    DllistNode *tmp = l->head;
    while (tmp) {
        if (tmp->data == data) {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}


// Setup and Teardown functions for test suite
static void DllistSetup(void)
{
    printf(ANSI_COLOR_GREEN);
    puts("\n\tSETUP::Calling dllistNew()");
    dllist = dllistNew();
    printf(ANSI_COLOR_YELLOW);
}

static void DllistTeardown(void)
{
    printf(ANSI_COLOR_GREEN);
    puts("\n\tSETUP::Calling dllistDestroy()");
    dllistDestroy(dllist);
    printf(ANSI_COLOR_RESET "\n");
}

// Testing code

static void CreateNew(void)
{
    Dllist *tmp = dllistNew();
    CU_ASSERT_PTR_NOT_NULL(tmp);
    free(tmp);
}

static void EmptyList(void)
{
    printf("\n\tIs the head empty?\n");
    if (dllist) {
        CU_ASSERT_PTR_NULL(dllist->head);
    }
}

static void AddOneNull(void)
{
    Dllist *tmp = NULL;
    printf("\n\n\tAdding 1 node to NULL list with value 25.\n");
    CU_ASSERT_FALSE(dllistAdd(tmp, 25));
}

static void AddOne(void)
{
    printf("\n\n\tAdding 1 node to list with value 100.\n");
    CU_ASSERT_TRUE(dllistAdd(dllist, 100));
    printDlist(dllist);
    printf("\n\tDoes the head match node, does the node point to NULL?\n");
    if (dllist) {
        CU_ASSERT_EQUAL(dllist->head->data, 100);
        CU_ASSERT_PTR_NULL(dllist->head->next);
        CU_ASSERT_PTR_NULL(dllist->head->prev);
    }
}

static void AddTen(void)
{
    printf("\n\n\tAdding values 1 through 10...\n");
    for (int x = 1; x < 11; ++x) {
        CU_ASSERT_TRUE(dllistAdd(dllist, x));
    }
    printDlist(dllist);
    puts("\tTesting list starts at 10 and goes to 1...");
    int count = 11;
    if (dllist) {
        DllistNode *tmp = dllist->head;
        while (tmp) {
            CU_ASSERT_EQUAL(tmp->data, --count);
            tmp = tmp->next;
        }
        CU_ASSERT_PTR_NULL(dllist->head->prev);
        tmp = findList(dllist, 1);
        CU_ASSERT_PTR_NULL(tmp->next);
        while (tmp->prev) {
            tmp = tmp->prev;
        }
        puts("\tChecking in reverse...");
        CU_ASSERT_PTR_EQUAL(dllist->head, tmp);
    }
}

static void FindOne(void)
{
    printf("\n\n\tAdding values 1 through 10...\n");
    for (int x = 1; x < 11; ++x) {
        dllistAdd(dllist, x);
    }
    printDlist(dllist);

    if (dllist) {
        DllistNode *test = findList(dllist, 5);
        printf("\tLooking for 5...Address: %p\n", &test);
        DllistNode *user = dllistFind(dllist, 5);
        printf("\tUser node data: %d - User node address: %p\n", user->data, &user);
        printf("\tTest node data: %d - Test node address: %p\n", test->data, &test);
        CU_ASSERT_PTR_EQUAL(test, user);
        CU_ASSERT_EQUAL(test->data, user->data);
    }
}

static void FindOneNull(void)
{
    Dllist *tmp = NULL;
    printf("\n\n\tFinding 2 in NULL list.\n");
    if (dllist) {
        DllistNode *user = dllistFind(tmp, 2);
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
        dllistAdd(dllist, x);
    }
    printDlist(dllist);
    printf("\n\n\tFinding 3 in list.\n");
    if (dllist) {
        DllistNode *user = dllistFind(dllist, 3);
        if (!user) {
            puts("\tNode pointer is NULL");
        }
        CU_ASSERT_PTR_NULL(user);
    }
}

static void FindFirstOne(void)
{
    printf("\n\n\tAdding values 1 through 5 with another 2...\n");
    for (int x = 1; x < 6; ++x) {
        dllistAdd(dllist, x);
    }
    dllistAdd(dllist, 2);
    printDlist(dllist);
    if (dllist) {
        DllistNode *test = findList(dllist, 2);
        printf("\tLooking for 5...Address: %p\n", &test);
        DllistNode *user = dllistFind(dllist, 2);
        printf("\tUser node data: %d - User node address: %p\n", user->data, &user);
        printf("\tTest node data: %d - Test node address: %p\n", test->data, &test);
        CU_ASSERT_PTR_EQUAL(test, user);
        CU_ASSERT_EQUAL(test->data, user->data);
    }
}

static void SortNull(void)
{
    Dllist *new = NULL;
    puts("\n\n\tSorting a NULL list..");
    CU_ASSERT_FALSE(dllistSort(new, dllistCompare));
}

static void SortEmpty(void)
{
    Dllist *new = dllistNew();
    puts("\n\n\tSorting an Empty list..");
    CU_ASSERT_FALSE(dllistSort(new, dllistCompare));
    free(new);
}

static void SortOne(void)
{
    puts("\n\n\tAdding 10 to the list...");
    CU_ASSERT_TRUE(dllistAdd(dllist, 10));
    printDlist(dllist);
    CU_ASSERT_TRUE(dllistSort(dllist, dllistCompare));
    printDlist(dllist);
    puts("\tNothing should change...");
    if (dllist) {
        CU_ASSERT_EQUAL(dllist->head->data, 10);
        CU_ASSERT_PTR_NULL(dllist->head->next);
        CU_ASSERT_PTR_NULL(dllist->head->prev);
    }
}

static void SortMany(void)
{
    printf("\n\n\tAdding values 1 through to 10...\n");
    for (int x = 1; x < 11; ++x) {
        dllistAdd(dllist, x);
    }
    printDlist(dllist);
    CU_ASSERT_TRUE(dllistSort(dllist, dllistCompare));
    puts("\tSorting list in ascending order...");
    if (dllist) {
        DllistNode *tmp = dllist->head;
        int check = 0;
        while (tmp) {
            printf("\tChecking Node %2d - Value: %2d\n", check, tmp->data);
            CU_ASSERT_EQUAL(tmp->data, ++check);
            tmp = tmp->next;
        }
        tmp = findList(dllist, 10);
        CU_ASSERT_PTR_NULL(tmp->next);
        while (tmp->prev) {
            tmp = tmp->prev;
        }
        puts("\tChecking in reverse...");
        CU_ASSERT_PTR_EQUAL(dllist->head, tmp);
    }
}

static void RemoveHeadNull(void)
{
    Dllist *tmp = NULL;
    puts("\n\n\tRemoving head from NULL list..");
    CU_ASSERT_PTR_NULL(dllistRmHead(tmp));
}

static void RemoveHeadEmpty(void)
{
    Dllist *tmp = dllistNew();
    puts("\n\n\tRemoving head from Empty list..");
    CU_ASSERT_PTR_NULL(dllistRmHead(tmp));
    free(tmp);
}

static void RemoveHead(void)
{
    printf("\n\n\tAdding values 1 through to 10...\n");
    for (int x = 1; x < 11; ++x) {
        dllistAdd(dllist, x);
    }
    printDlist(dllist);
    if (dllist) {
        DllistNode *tmp = dllistRmHead(dllist);
        CU_ASSERT_EQUAL(tmp->data, 10);
        free(tmp);
        CU_ASSERT_EQUAL(dllist->head->data, 9);
        CU_ASSERT_PTR_NULL(dllist->head->prev);
        printDlist(dllist);
        tmp = findList(dllist, 1);
        CU_ASSERT_PTR_NULL(tmp->next);
        while (tmp->prev) {
            tmp = tmp->prev;
        }
        puts("\tChecking in reverse...");
        CU_ASSERT_PTR_EQUAL(dllist->head, tmp);
    }
}

static void RemoveNull(void)
{
    Dllist *tmp = NULL;
    puts("\n\n\tRemoving from NULL list..");
    CU_ASSERT_PTR_NULL(dllistRmHead(tmp));
}

static void RemoveEmpty(void)
{
    Dllist *tmp = dllistNew();
    puts("\n\n\tRemoving from Empty list..");
    CU_ASSERT_PTR_NULL(dllistRmHead(tmp));
    free(tmp);
}

static void RemoveOne(void)
{
    printf("\n\n\tAdding values 1 through 5...\n");
    for (int x = 1; x < 6; ++x) {
        CU_ASSERT_TRUE(dllistAdd(dllist, x));
    }
    printDlist(dllist);
    puts("\n\tRemoving 5 and checking list til final node->next...\n");
    if (dllist) {
        DllistNode *tmp = dllistRm(dllist, 5);
        CU_ASSERT_EQUAL(tmp->data, 5);
        free(tmp);
        tmp = dllist->head;
        int count = 0;
        while (tmp) {
            ++count;
            tmp = tmp->next;
        }
        CU_ASSERT_EQUAL(count, 4);
        printDlist(dllist);
        tmp = findList(dllist, 4);
        while (tmp->prev) {
            tmp = tmp->prev;
        }
        puts("\tChecking in reverse...");
        CU_ASSERT_PTR_EQUAL(dllist->head, tmp);
    }
}

static void RemoveTwo(void)
{
    printf("\n\n\tAdding values 1 through 5...\n");
    for (int x = 1; x < 6; ++x) {
        CU_ASSERT_TRUE(dllistAdd(dllist, x));
    }
    printDlist(dllist);
    puts("\n\tRemoving 1 then 3 and checking list til final node->next...\n");
    if (dllist) {
        DllistNode *tmp = dllistRm(dllist, 1);
        CU_ASSERT_EQUAL(tmp->data, 1);
        free(tmp);
        tmp = dllistRm(dllist, 3);
        CU_ASSERT_EQUAL(tmp->data, 3);
        free(tmp);
        tmp = dllist->head;
        int count = 0;
        while (tmp) {
            ++count;
            tmp = tmp->next;
        }
        CU_ASSERT_EQUAL(count, 3);
        printDlist(dllist);
        tmp = findList(dllist, 5);
        while (tmp->prev) {
            tmp = tmp->prev;
        }
        puts("\tChecking in reverse...");
        CU_ASSERT_PTR_EQUAL(dllist->head, tmp);
    }
}

static void RemoveOneFromOne(void)
{
    printf("\n\n\tAdding value 1...\n");
    CU_ASSERT_TRUE(dllistAdd(dllist, 1));
    printDlist(dllist);
    puts("\tRemoving value 1 and validating list...");
    if (dllist) {
        DllistNode *tmp = dllistRm(dllist, 1);
        CU_ASSERT_EQUAL(tmp->data, 1);
        free(tmp);
        CU_ASSERT_PTR_NULL(dllist->head);
        printDlist(dllist);
    }
}

static void InsertAfterNull(void)
{
    Dllist *tmp = NULL;
    puts("\n\n\tInserting 1 after 10 in NULL list..");
    CU_ASSERT_FALSE(dllistAddAfter(tmp, 1, 10));
}

static void InsertAfterEmpty(void)
{
    Dllist *tmp = dllistNew();
    puts("\n\n\tInserting 1 after 10 in Empty list..");
    CU_ASSERT_FALSE(dllistAddAfter(tmp, 1, 10));
    free(tmp);
}

static void InsertAfterOne(void)
{
    printf("\n\n\tAdding values 1 through 5...\n");
    for (int x = 1; x < 6; ++x) {
        CU_ASSERT_TRUE(dllistAdd(dllist, x));
    }
    printDlist(dllist);
    puts("\tInserting 10 after 1...");
    CU_ASSERT_TRUE(dllistAddAfter(dllist, 10, 1));
    printDlist(dllist);
    if (dllist) {
        DllistNode *tmp = findList(dllist, 10);
        CU_ASSERT_EQUAL(tmp->data, 10);
        CU_ASSERT_PTR_NULL(tmp->next);
        puts("\tChecking in reverse...");
        while (tmp->prev) {
            tmp = tmp->prev;
        }
        CU_ASSERT_PTR_EQUAL(dllist->head, tmp);
    }
}

static void InsertAfterTwo(void)
{
    printf("\n\n\tAdding values 1 through 5...\n");
    for (int x = 1; x < 6; ++x) {
        CU_ASSERT_TRUE(dllistAdd(dllist, x));
    }
    printDlist(dllist);
    puts("\tInserting 10 after 3...");
    CU_ASSERT_TRUE(dllistAddAfter(dllist, 10, 3));
    puts("\tInserting 20 after 10...");
    CU_ASSERT_TRUE(dllistAddAfter(dllist, 20, 10));

    puts("\tChecking that 10 and 20 are in the right spots...");
    if (dllist) {
        DllistNode *tmp = dllist->head;
        int count = 0;
        bool foundTen = false;
        bool foundTwenty = false;
        while (tmp) {
            ++count;
            if (tmp->data == 10 && count == 4) {
                printf("\tFound 10 in spot %d.\n", count);
                CU_PASS();
                foundTen = true;
            } else if (tmp->data == 10) {
                printf("\tFound 10 in spot %d.\n", count);
                CU_FAIL("Wrong index for insertion.");
                foundTen = true;
            }
            if (tmp->data == 20 && count == 5) {
                printf("\tFound 20 in spot %d.\n", count);
                CU_PASS();
                foundTwenty = true;
            }  else if (tmp->data == 20) {
                printf("\tFound 20 in spot %d.\n", count);
                CU_FAIL("Wrong index for insertion.");
                foundTwenty = true;
            }
            tmp = tmp->next;
        }
        CU_ASSERT_TRUE(foundTen);
        CU_ASSERT_TRUE(foundTwenty);
        printDlist(dllist);
        tmp = findList(dllist, 1);
        CU_ASSERT_PTR_NULL(tmp->next);
        puts("\tChecking in reverse...");
        while (tmp->prev) {
            tmp = tmp->prev;
        }
        CU_ASSERT_PTR_EQUAL(dllist->head, tmp);
    }
}

static void InsertBeforeOne(void)
{
    printf("\n\n\tAdding values 1 through 5...\n");
    for (int x = 1; x < 6; ++x) {
        CU_ASSERT_TRUE(dllistAdd(dllist, x));
    }
    printDlist(dllist);
    puts("\tInserting 15 before 3...");
    CU_ASSERT_TRUE(dllistAddBefore(dllist, 15, 3));
    if (dllist) {
        DllistNode *tmp = dllist->head;
        int count = 0;
        bool foundFifteen = false;
        while (tmp) {
            ++count;
            if (tmp->data == 15 && count == 3) {
                printf("\tFound 15 in spot %d.\n", count);
                foundFifteen = true;
                CU_PASS();
            } else if (tmp->data == 15) {
                printf("\tFound 15 in spot %d.\n", count);
                CU_FAIL("Wrong index for insertion.");
                foundFifteen = true;
            }
            tmp = tmp->next;
        }
        CU_ASSERT_TRUE(foundFifteen);
        CU_ASSERT_EQUAL(count, 6);
        printDlist(dllist);
        tmp = findList(dllist, 1);
        CU_ASSERT_PTR_NULL(tmp->next);
        puts("\tChecking in reverse...");
        while (tmp->prev) {
            tmp = tmp->prev;
        }
        CU_ASSERT_PTR_EQUAL(dllist->head, tmp);
    }
}

static void InsertBeforeTwo(void)
{
    printf("\n\n\tAdding values 1 through 5...\n");
    for (int x = 1; x < 6; ++x) {
        CU_ASSERT_TRUE(dllistAdd(dllist, x));
    }
    printDlist(dllist);
    puts("\tInserting 15 before 5...");
    CU_ASSERT_TRUE(dllistAddBefore(dllist, 15, 5));
    puts("\tInserting 10 before 1...");
    CU_ASSERT_TRUE(dllistAddBefore(dllist, 10, 1));
    if (dllist) {
        DllistNode *tmp = dllist->head;
        int count = 0;
        bool foundFifteen = false;
        bool foundTen = false;
        while (tmp) {
            ++count;
            if (tmp->data == 15 && count == 1) {
                printf("\tFound 15 in spot %d.\n", count);
                foundFifteen = true;
                CU_PASS();
            } else if (tmp->data == 15) {
                printf("\tFound 15 in spot %d.\n", count);
                CU_FAIL("Wrong index for insertion.");
                foundFifteen = true;
            }
            if (tmp->data == 10 && count == 6) {
                printf("\tFound 10 in spot %d.\n", count);
                foundTen = true;
                CU_PASS();
            } else if (tmp->data == 10) {
                printf("\tFound 10 in spot %d.\n", count);
                CU_FAIL("Wrong index for insertion.");
                foundTen = true;
            }
            tmp = tmp->next;
        }
        CU_ASSERT_TRUE(foundFifteen);
        CU_ASSERT_TRUE(foundTen);
        CU_ASSERT_EQUAL(count, 7);
        printDlist(dllist);
        tmp = findList(dllist, 1);
        CU_ASSERT_PTR_NULL(tmp->next);
        puts("\tChecking in reverse...");
        while (tmp->prev) {
            tmp = tmp->prev;
        }
        CU_ASSERT_PTR_EQUAL(dllist->head, tmp);
    }
}

static CU_TestInfo listTests[] = {
    // Name, functionThatRunsTest
    { "NewList", CreateNew },
    { "Empty List", EmptyList },
    { "NULL list add one", AddOneNull },
    { "Testing add one", AddOne },
    { "Testing add ten", AddTen },
    { "Finding one", FindOne },
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
    { "Insert one values before", InsertBeforeOne },
    { "Insert two values before", InsertBeforeTwo },
    CU_TEST_INFO_NULL
};

CU_SuiteInfo dllistSuite = {
    // Name, suiteSetup, suiteTeardown, testSetup, testTeardown, arrayOfTests
    "Doubly Linked-list Tests",
    NULL,
    NULL,
    DllistSetup,
    DllistTeardown,
    listTests
};
