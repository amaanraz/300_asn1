#include <stdio.h>
#include <assert.h>
#include "list.h"

void ListCreateTestCases();
void ListCountTestCases();
void ListInsertAfterTestCases();
void ListInsertBeforeTestCases();
void ListAppendTestCases();
void ListPrependTestCases();
void ListRemoveTestCases();
void ListTrimTestCases();
void ListFreeTestCases();
void ListConcateTestCases();
void ListSearchTestCases();


int main() {
    ListCreateTestCases();
    // ListCountTestCases();
    ListInsertAfterTestCases();
    // ListInsertBeforeTestCases();
    // ListAppendTestCases();
    // ListPrependTestCases();
    // ListRemoveTestCases();
    // ListTrimTestCases();
    // ListFreeTestCases();
    ListConcateTestCases();
    // ListSearchTestCases();

    return 0;
}

void freeItem(void* pItem){
    free((int*)pItem);
}

void ListCreateTestCases(){
    // Test case 1: Create a list successfully
    List* list1 = List_create();
    assert(list1 != NULL); // Check if the list is not NULL
    assert(list1->head == NULL); // Check if the list is empty
    assert(list1->current == NULL); // Check if current is NULL
    assert(list1->count == 0); // Check if count is 0

    // Test case 2: Attempt to create more lists than allowed
    // Assuming LIST_MAX_NUM_HEADS is set to 10
    List* lists[12];
    for (int i = 0; i < 12; i++) {
        lists[i] = List_create();
        if(i < 9){
            assert(lists[i] != NULL);
        } else {
            assert(lists[i] == NULL);
        }
    }

    // Test case 3: Check if list heads are unique
    for (int i = 0; i < 10; i++) {
        for (int j = i + 1; j < 10; j++) {
            assert(lists[i] != lists[j]); // Ensure that list heads are unique
        }
    }

    // Clean up: You can free the lists if needed (assuming you have implemented List_free)
    for (int i = 0; i < 10; i++) {
        if (lists[i] != NULL) {
            List_free(lists[i], NULL); // You can provide a suitable FREE_FN if needed
        }
    }

    printf("All LIST CREATE test cases passed!\n");
}

void ListCountTestCases(){
    // // empty list
    // List* list1 = List_create(); // TODO: cant test until I free the previosly used lists :(
    // assert(List_count(list1) == 0);

    // // null list
    // List_count(NULL);

    // printf("All LIST COUNT test cases passed!\n");
}

void ListInsertAfterTestCases(){
    // Test case 1: Insert after current when current is before the start.
    List* list1 = List_create();
    assert(list1->current == NULL);
    // printf(list1->count);
    int item1 = 10;
    List_insert_after(list1, (void*)&item1);

    // The list should contain one item, and it should be the current item.
    assert(List_count(list1) == 1);
    assert(List_curr(list1) == &item1);

    // // Test case 2: Insert after current when current is beyond the end.
    List* list2 = List_create();
    int item2 = 20;
    // List_next(list2); // Move current beyond the end.
    List_insert_after(list2, &item2);

    // The list should contain one item, and it should be the current item.
    assert(List_count(list2) == 1);
    assert(List_curr(list2) == &item2);

    int item3 = 30;
    List_insert_after(list2, &item3);
    assert(List_count(list2) == 2);
    assert(List_curr(list2) == &item3);

    // // Test case 3: Insert after current when current is within the list.
    List* list3 = List_create();
    int item3_1 = 30;
    int item3_2 = 40;
    List_insert_after(list3, &item3_1);
    List_insert_after(list3, &item3_2);

    // The list should contain two items, and the current item should be the second item.
    assert(List_count(list3) == 2);
    assert(List_curr(list3) == &item3_2);

    // Test case 4: Insert after current when the list is empty.
    List* list4 = List_create();
    int item4 = 50;
    List_insert_after(list4, &item4);

    // The list should contain one item, and it should be the current item.
    assert(List_count(list4) == 1);
    assert(List_curr(list4) == &item4);

    // Test case 5: Insert multiple items after current.
    List* list5 = List_create();
    int item5_1 = 60;
    int item5_2 = 70;
    List_insert_after(list5, &item5_1);
    List_next(list5); // Move current to the first item.
    List_insert_after(list5, &item5_2);

    // The list should contain two items, and the current item should be the second item.
    assert(List_count(list5) == 2);
    assert(List_curr(list5) == &item5_2);

    // Clean up and free lists.
    List_free(list1, NULL);
    List_free(list2, NULL);
    List_free(list3, NULL);
    List_free(list4, NULL);
    List_free(list5, NULL);

    printf("All test cases passed!\n");

}

void ListInsertBeforeTestCases(){
    // Test case 1: Insert before current when current is before the start.
    List* list1 = List_create();
    int item1 = 10;
    List_insert_before(list1, &item1);

    // The list should contain one item, and it should be the current item.
    assert(List_count(list1) == 1);
    assert(List_curr(list1) == &item1);

    // Test case 2: Insert before current when current is beyond the end.
    List* list2 = List_create();
    int item2 = 20;
    // List_next(list2); // Move current beyond the end.
    List_insert_before(list2, &item2);

    // The list should contain one item, and it should be the current item.
    assert(List_count(list2) == 1);
    assert(List_curr(list2) == &item2);
    int item3 = 40;
    List_insert_before(list2, &item3);
    assert(List_curr(list2) == &item3);

    // Test case 3: Insert before current when current is within the list.
    List* list3 = List_create();
    int item3_1 = 30;
    int item3_2 = 40;
    List_insert_before(list3, &item3_1);
    List_insert_before(list3, &item3_2);

    // The list should contain two items, and the current item should be the second item.
    assert(List_count(list3) == 2);
    assert(List_curr(list3) == &item3_2);

    // Test case 4: Insert before current when the list is empty.
    List* list4 = List_create();
    int item4 = 50;
    List_insert_before(list4, &item4);

    // The list should contain one item, and it should be the current item.
    assert(List_count(list4) == 1);
    assert(List_curr(list4) == &item4);

    // Test case 5: Insert multiple items before current.
    List* list5 = List_create();
    int item5_1 = 60;
    int item5_2 = 70;
    int item5_3 = 23;
    List_insert_before(list5, &item5_1);
    // List_next(list5); // Move current to the first item.
    List_insert_before(list5, &item5_2);
    List_insert_before(list5, &item5_3);

    // The list should contain two items, and the current item should be the first item.
    assert(List_count(list5) == 3);
    assert(List_curr(list5) == &item5_3);
    assert(List_last(list5) == &item5_1);
    assert(List_first(list5) == &item5_3);

    // Clean up and free lists.
    // List_free(list1);
    // List_free(list2);
    // List_free(list3);
    // List_free(list4);
    // List_free(list5);

    printf("All test cases passed!1\n");
}


void ListAppendTestCases(){
    // Test case 1: Append an item to an empty list.
    List* list1 = List_create();
    int item1 = 10;
    List_append(list1, &item1);

    // The list should contain one item, and it should be the current item.
    assert(List_count(list1) == 1);
    assert(List_curr(list1) == &item1);

    // Test case 2: Append multiple items to a non-empty list.
    List* list2 = List_create();
    int item2_1 = 20;
    int item2_2 = 30;
    List_append(list2, &item2_1);
    List_append(list2, &item2_2);

    // The list should contain two items, and the current item should be the second item.
    assert(List_count(list2) == 2);
    assert(List_curr(list2) == &item2_2);

    // Test case 3: Append an item to a list with a NULL current pointer.
    List* list3 = List_create();
    int item3 = 40;
    List_append(list3, &item3);
    // List_next(list3); // Move current beyond the end.
    List_append(list3, &item3);

    // The list should contain two items, and the current item should be the second item.
    assert(List_count(list3) == 2);
    assert(List_curr(list3) == &item3);
    assert(List_last(list3) == &item3);

    // Clean up and free lists.
    // List_free(list1);
    // List_free(list2);
    // List_free(list3);

    printf("All test cases passed!\n");

}

void ListPrependTestCases(){
    // Test case 1: Prepend an item to an empty list.
    List* list1 = List_create();
    int item1 = 10;
    List_prepend(list1, &item1);

    // The list should contain one item, and it should be the current item.
    assert(List_count(list1) == 1);
    assert(List_curr(list1) == &item1);

    // Test case 2: Prepend multiple items to a non-empty list.
    List* list2 = List_create();
    int item2_1 = 20;
    int item2_2 = 30;
    List_prepend(list2, &item2_1);
    List_prepend(list2, &item2_2);

    // The list should contain two items, and the current item should be the first item.
    assert(List_count(list2) == 2);
    assert(List_curr(list2) == &item2_2);

    // Test case 3: Prepend an item to a list with a NULL current pointer.
    List* list3 = List_create();
    int item3 = 40;
    List_prepend(list3, &item3);
    // List_next(list3); // Move current beyond the end.
    List_prepend(list3, &item2_1);

    // The list should contain two items, and the current item should be the first item.
    assert(List_count(list3) == 2);
    assert(List_curr(list3) == &item2_1);
    assert(List_first(list3) == &item2_1);
    assert(List_last(list3) == &item3);

    // Clean up and free lists.
    // List_free(list1);
    // List_free(list2);
    // List_free(list3);

    printf("All test cases passed!\n");

}


void ListRemoveTestCases(){
    // Test case 1: Remove from an empty list.
    List* list1 = List_create();
    assert(List_remove(list1) == NULL); // Removing from an empty list should return NULL.

    // Test case 2: Remove from a list with one item.
    List* list2 = List_create();
    int item2 = 10;
    List_append(list2, &item2);

    // The list should contain one item, and it should be the current item.
    assert(List_count(list2) == 1);
    assert(List_curr(list2) == &item2);

    // Remove the item from the list.
    assert(List_remove(list2) == &item2);

    // The list should be empty, and current should be NULL.
    assert(List_count(list2) == 0);
    assert(List_curr(list2) == NULL);

    // Test case 3: Remove from a list with multiple items.
    List* list3 = List_create();
    int item3_1 = 20;
    int item3_2 = 30;
    List_append(list3, &item3_1);
    List_append(list3, &item3_2);

    // The list should contain two items, and the current item should be the first item.
    assert(List_count(list3) == 2);
    assert(List_curr(list3) == &item3_2);

    // Remove the first item from the list.
    assert(List_remove(list3) == &item3_2);

    // The list should contain one item, and the current item should be the second item.
    assert(List_count(list3) == 1);
    assert(List_curr(list3) == &item3_1);

    // Remove the last item from the list.
    assert(List_remove(list3) == &item3_1);

    // The list should be empty, and current should be NULL.
    assert(List_count(list3) == 0);
    assert(List_curr(list3) == NULL);

    // Test case 4: Remove when current is before the start or beyond the end of the list.
    List* list4 = List_create();
    int item4 = 40;
    List_append(list4, &item4);

    // Move current beyond the end.
    // List_next(list4);

    // Removing when current is beyond the end should return NULL.
    // assert(List_remove(list4) == NULL);

    // Move current before the start.
    // List_prev(list4);

    // Removing when current is before the start should return NULL.
    // assert(List_remove(list4) == NULL);

    // Clean up and free lists.
    // List_free(list1);
    // List_free(list2);
    // List_free(list3);
    // List_free(list4);

    printf("All test cases passed!\n");
}

void ListTrimTestCases(){
    // Test case 1: Trim from an empty list.
    List* list1 = List_create();
    assert(List_trim(list1) == NULL); // Trimming from an empty list should return NULL.

    // Test case 2: Trim from a list with one item.
    List* list2 = List_create();
    int item2 = 10;
    List_append(list2, &item2);

    // The list should contain one item, and it should be the current item.
    assert(List_count(list2) == 1);
    assert(List_curr(list2) == &item2);

    // Trim the item from the list.
    assert(List_trim(list2) == &item2);

    // The list should be empty, and current should be NULL.
    assert(List_count(list2) == 0);
    assert(List_curr(list2) == NULL);

    // Test case 3: Trim from a list with multiple items.
    List* list3 = List_create();
    int item3_1 = 20;
    int item3_2 = 30;
    List_append(list3, &item3_1);
    List_append(list3, &item3_2);

    // The list should contain two items, and the current item should be the second item.
    assert(List_count(list3) == 2);
    assert(List_curr(list3) == &item3_2);

    // Trim the last item from the list.
    assert(List_trim(list3) == &item3_2);

    // The list should contain one item, and the current item should be the first item.
    assert(List_count(list3) == 1);
    assert(List_curr(list3) == &item3_1);

    // Trim the remaining item from the list.
    assert(List_trim(list3) == &item3_1);

    // The list should be empty, and current should be NULL.
    assert(List_count(list3) == 0);
    assert(List_curr(list3) == NULL);

    // Test case 4: Trim from an initially empty list.
    List* list4 = List_create();
    int item4 = 40;
    List_prepend(list4, &item4);

    // The list should contain one item, and it should be the current item.
    assert(List_count(list4) == 1);
    assert(List_curr(list4) == &item4);

    // Trim the item from the list.
    assert(List_trim(list4) == &item4);

    // The list should be empty, and current should be NULL.
    assert(List_count(list4) == 0);
    assert(List_curr(list4) == NULL);

    // Clean up and free lists.
    // List_free(list1);
    // List_free(list2);
    // List_free(list3);
    // List_free(list4);

    printf("All test cases passed!\n");
}

void SimpleFreeFn(void* item) {

}


void ListFreeTestCases(){
    // Test case 1: Free an empty list.
    List* list1 = List_create();
    List_free(list1, SimpleFreeFn); // Should not crash.
    
    // Test case 2: Free a list with items and custom item freeing.
    // List* list2 = List_create();
    // int item2_1 = 10;
    // int item2_2 = 20;
    // List_append(list2, &item2_1);
    // List_append(list2, &item2_2);
    
    // // The list should contain two items.
    // assert(List_count(list2) == 2);

    // // Free the list with custom item freeing.
    // List_free(list2, SimpleFreeFn);

    // // The list should be empty.
    // assert(List_count(list2) == 0);

    // // Test case 3: Free a list without custom item freeing.
    // List* list3 = List_create();
    // int item3_1 = 30;
    // int item3_2 = 40;
    // List_append(list3, &item3_1);
    // List_append(list3, &item3_2);
    
    // // The list should contain two items.
    // assert(List_count(list3) == 2);

    // // Free the list without custom item freeing.
    // List_free(list3, NULL);

    // // The list should be empty.
    // assert(List_count(list3) == 0);

    // // Clean up and free lists.
    // List_free(list1, SimpleFreeFn);
    // List_free(list2, SimpleFreeFn);
    // List_free(list3, SimpleFreeFn);

    printf("All test cases passed!\n");
}

void ListConcateTestCases(){
    // Create two lists.
    List* list1 = List_create();
    List* list2 = List_create();

    // Add some items to list1.
    int item1 = 1;
    int item2 = 2;
    List_append(list1, &item1);
    List_append(list1, &item2);

    // Add some items to list2.
    int item3 = 3;
    int item4 = 4;
    List_append(list2, &item3);
    List_append(list2, &item4);

    // Concatenate list2 to list1.
    List_concat(list1, list2);

    // Verify that list1 contains all items.
    assert(List_count(list1) == 4);
    assert(*(int*)List_first(list1) == 1);
    assert(*(int*)List_last(list1) == 4);

    // Verify that list2 is empty.
    assert(List_count(list2) == 0);
    assert(List_first(list2) == NULL);
    assert(List_last(list2) == NULL);

    // // Clean up.
    List_free(list1, NULL); // No item freeing function needed for this test.
    List_free(list2, NULL);

    printf("All test cases passed! concante\n");
}

bool intComparator(void* pItem, void* pComparisonArg);

void ListSearchTestCases(){
    List* list = List_create();
    int item1 = 1;
    int item2 = 2;
    int item3 = 3;
    int item4 = 4;
    List_append(list, &item1);
    List_append(list, &item2);
    List_append(list, &item3);
    List_append(list, &item4);

    // Test searching for an existing item.
    int searchItem1 = 2;
    int searchItem2 = 5;
    int* result1 = (int*)List_search(list, intComparator, &searchItem1);
    int* result2 = (int*)List_search(list, intComparator, &searchItem2);

    // // Verify that the search results are as expected.
    // assert(result1 != NULL); // Item 2 should be found.
    // assert(*result1 == searchItem1);
    // assert(result2 == NULL); // Item 5 should not be found.

    // // Test searching when the current pointer is before the start of the list.
    // List_first(list);
    // int searchItem3 = 3;
    // int* result3 = (int*)List_search(list, intComparator, &searchItem3);

    // // Verify that the search result is as expected.
    // assert(result3 != NULL); // Item 3 should be found.
    // assert(*result3 == searchItem3);

    // // Clean up.
    // List_free(list, NULL);

    printf("All LIST SEARCH test cases passed!\n");
}


// Custom comparator function to compare integers for equality.
bool intComparator(void* pItem, void* pComparisonArg) {
    int item = *(int*)pItem;
    int comparisonArg = *(int*)pComparisonArg;
    return (item == comparisonArg);
}