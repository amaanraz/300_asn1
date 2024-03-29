#include <stdio.h>
#include <assert.h>
#include "list.h"

void ListCreateTestCases();
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
    // ListCreateTestCases();
    ListInsertAfterTestCases();
    
    // ListAppendTestCases();
    // ListPrependTestCases();
    // ListRemoveTestCases();
    // ListTrimTestCases();
    // ListInsertBeforeTestCases();
    // ListConcateTestCases();
    // ListSearchTestCases();

    return 0;
}

void freeItem(void* pItem){
    pItem = NULL;
}

void ListCreateTestCases(){
    //Create a list successfully
    List* list1 = List_create();
    assert(list1 != NULL);
    assert(list1->head == NULL); 
    assert(list1->current == NULL); 
    assert(list1->count == 0); 

    
    List* lists[12];
    for (int i = 0; i < 12; i++) {
        lists[i] = List_create();
        if(i < 9){
            assert(lists[i] != NULL);
        } else {
            assert(lists[i] == NULL);
        }
    }

    
    for (int i = 0; i < 10; i++) {
        for (int j = i + 1; j < 10; j++) {
            assert(lists[i] != lists[j]); 
        }
    }

    // free
    for (int i = 0; i < 10; i++) {
        if (lists[i] != NULL) {
            List_free(lists[i], freeItem);
        }
    }

    // for (int i = 0; i < 12; i++) {
    //     lists[i] = List_create();
    //     if(i < 9){
    //         assert(lists[i] != NULL);
    //     } else {
    //         assert(lists[i] == NULL);
    //     }
    // }

    printf("All LIST CREATE test cases passed!\n");
}


void ListInsertAfterTestCases(){
   
    List* list1 = List_create();
    assert(list1->current == NULL);
    // printf(list1->count);
    int item1 = 10;
    List_insert_after(list1, &item1);

   
    assert(List_count(list1) == 1);
    assert(List_curr(list1) == &item1);

  
    List* list2 = List_create();
    int item2 = 20;
    // List_next(list2); // Move current beyond the end.
    List_insert_after(list2, &item2);


    assert(List_count(list2) == 1);
    assert(List_curr(list2) == &item2);

    int item3 = 30;
    List_insert_after(list2, &item3);
    assert(List_count(list2) == 2);
    assert(List_curr(list2) == &item3);


    List* list3 = List_create();
    int item3_1 = 30;
    int item3_2 = 40;
    List_insert_after(list3, &item3_1);
    List_insert_after(list3, &item3_2);


    assert(List_count(list3) == 2);
    assert(List_curr(list3) == &item3_2);


    List* list4 = List_create();
    int item4 = 50;
    List_insert_after(list4, &item4);


    assert(List_count(list4) == 1);
    assert(List_curr(list4) == &item4);


    List* list5 = List_create();
    int item5_1 = 60;
    int item5_2 = 70;
    List_insert_after(list5, &item5_1);
    List_next(list5); 
    List_insert_after(list5, &item5_2);

 
    assert(List_count(list5) == 2);
    assert(List_curr(list5) == &item5_2);

    // Clean up and free lists.
    List_free(list1, freeItem);
    List_free(list2, freeItem);
    List_free(list3, freeItem);
    List_free(list4, freeItem);
    List_free(list5, freeItem);

    printf("All test cases passed!\n");

}

void ListInsertBeforeTestCases(){
   
    List* list1 = List_create();
    int item1 = 10;
    List_insert_before(list1, &item1);

  
    assert(List_count(list1) == 1);
    assert(List_curr(list1) == &item1);

 
    List* list2 = List_create();
    int item2 = 20;
    // List_next(list2); // Move current beyond the end.
    List_insert_before(list2, &item2);

    
    assert(List_count(list2) == 1);
    assert(List_curr(list2) == &item2);
    int item3 = 40;
    List_insert_before(list2, &item3);
    assert(List_curr(list2) == &item3);

    List* list3 = List_create();
    int item3_1 = 30;
    int item3_2 = 40;
    List_insert_before(list3, &item3_1);
    List_insert_before(list3, &item3_2);


    assert(List_count(list3) == 2);
    assert(List_curr(list3) == &item3_2);


    List* list4 = List_create();
    int item4 = 50;
    List_insert_before(list4, &item4);

 
    assert(List_count(list4) == 1);
    assert(List_curr(list4) == &item4);


    List* list5 = List_create();
    int item5_1 = 60;
    int item5_2 = 70;
    int item5_3 = 23;
    List_insert_before(list5, &item5_1);
    // List_next(list5); // Move current to the first item.
    List_insert_before(list5, &item5_2);
    List_insert_before(list5, &item5_3);

  
    assert(List_count(list5) == 3);
    assert(List_curr(list5) == &item5_3);
    assert(List_last(list5) == &item5_1);
    assert(List_first(list5) == &item5_3);

    List_free(list1,freeItem);
    List_free(list2,freeItem);
    List_free(list3,freeItem);
    List_free(list4,freeItem);
    List_free(list5,freeItem);

    printf("All test cases passed!1\n");
}


void ListAppendTestCases(){

    List* list1 = List_create();
    int item1 = 10;
    List_append(list1, &item1);

    assert(List_count(list1) == 1);
    assert(List_curr(list1) == &item1);

    List* list2 = List_create();
    int item2_1 = 20;
    int item2_2 = 30;
    List_append(list2, &item2_1);
    List_append(list2, &item2_2);

    assert(List_count(list2) == 2);
    assert(List_curr(list2) == &item2_2);

    List* list3 = List_create();
    int item3 = 40;
    List_append(list3, &item3);
    // List_next(list3); // Move current beyond the end.
    List_append(list3, &item3);

    assert(List_count(list3) == 2);
    assert(List_curr(list3) == &item3);
    assert(List_last(list3) == &item3);

    // Clean up and free lists.
    List_free(list1, freeItem);
    List_free(list2, freeItem);
    List_free(list3, freeItem);

    printf("All test cases passed!\n");

}

void ListPrependTestCases(){
    List* list1 = List_create();
    int item1 = 10;
    List_prepend(list1, &item1);

    assert(List_count(list1) == 1);
    assert(List_curr(list1) == &item1);

    List* list2 = List_create();
    int item2_1 = 20;
    int item2_2 = 30;
    List_prepend(list2, &item2_1);
    List_prepend(list2, &item2_2);

    assert(List_count(list2) == 2);
    assert(List_curr(list2) == &item2_2);

    List* list3 = List_create();
    int item3 = 40;
    List_prepend(list3, &item3);
    // List_next(list3); // Move current beyond the end.
    List_prepend(list3, &item2_1);

    assert(List_count(list3) == 2);
    assert(List_curr(list3) == &item2_1);
    assert(List_first(list3) == &item2_1);
    assert(List_last(list3) == &item3);

    // Clean up and free lists.
    List_free(list1,freeItem);
    List_free(list2,freeItem);
    List_free(list3,freeItem);

    printf("All test cases passed!\n");

}


void ListRemoveTestCases(){
    List* list1 = List_create();
    assert(List_remove(list1) == NULL); 

    List* list2 = List_create();
    int item2 = 10;
    List_append(list2, &item2);

    assert(List_count(list2) == 1);
    assert(List_curr(list2) == &item2);

    assert(List_remove(list2) == &item2);

    assert(List_count(list2) == 0);
    // printf(List_curr(list2));
    assert(List_curr(list2) == NULL);

    List* list3 = List_create();
    int item3_1 = 20;
    int item3_2 = 30;
    List_append(list3, &item3_1);
    List_append(list3, &item3_2);

    assert(List_count(list3) == 2);
    assert(List_curr(list3) == &item3_2);

    assert(List_remove(list3) == &item3_2);

    assert(List_count(list3) == 1);
    // assert(List_curr(list3) == &item3_1);

    assert(List_remove(list3) == NULL);

    assert(List_count(list3) == 0);
    assert(List_curr(list3) == NULL);

    List* list4 = List_create();
    int item4 = 40;
    List_append(list4, &item4);

    // List_next(list4);

    // assert(List_remove(list4) == NULL);

    // List_prev(list4);

    // assert(List_remove(list4) == NULL);

    List_free(list1, freeItem);
    List_free(list2, freeItem);
    List_free(list3, freeItem);
    List_free(list4, freeItem);

    printf("All test cases passed!\n");
}

void ListTrimTestCases(){
    List* list1 = List_create();
    assert(List_trim(list1) == NULL); 

    List* list2 = List_create();
    int item2 = 10;
    List_append(list2, &item2);

    assert(List_count(list2) == 1);
    assert(List_curr(list2) == &item2);

    assert(List_trim(list2) == &item2);

    assert(List_count(list2) == 0);
    // assert(List_curr(list2) == NULL);

    List* list3 = List_create();
    int item3_1 = 20;
    int item3_2 = 30;
    List_append(list3, &item3_1);
    List_append(list3, &item3_2);

    assert(List_count(list3) == 2);
    assert(List_curr(list3) == &item3_2);

    assert(List_trim(list3) == &item3_2);

    assert(List_count(list3) == 1);
    assert(List_curr(list3) == &item3_1);

    assert(List_trim(list3) == &item3_1);

    assert(List_count(list3) == 0);
    // assert(List_curr(list3) == NULL);

    List* list4 = List_create();
    int item4 = 40;
    List_append(list4, &item4); // TODO: FIGURE OUT PREPEND

    assert(List_count(list4) == 1);
    assert(List_curr(list4) == &item4);

    assert(List_trim(list4) == &item4);

    // assert(List_count(list4) == 0);
    // assert(List_curr(list4) == NULL);

    // Clean up and free lists.
    List_free(list1, freeItem);
    List_free(list2, freeItem);
    List_free(list3, freeItem);
    List_free(list4, freeItem);

    printf("All test cases passed!\n");
}


void ListConcateTestCases(){
    // Create two lists.
    List* list1 = List_create();
    List* list2 = List_create();


    int item1 = 1;
    int item2 = 2;
    List_append(list1, &item1);
    List_append(list1, &item2);

    int item3 = 3;
    int item4 = 4;
    List_append(list2, &item3);
    List_append(list2, &item4);

    List_concat(list1, list2);

    assert(List_count(list1) == 4);
    assert(*(int*)List_first(list1) == 1);
    assert(*(int*)List_last(list1) == 4);

    assert(List_count(list2) == 0);
    assert(List_first(list2) == NULL);
    assert(List_last(list2) == NULL);

    // Clean up.
    List_free(list1, freeItem); 
    List_free(list2, freeItem);

    printf("All concante test cases passed! \n");
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
    // int* result2 = (int*)List_search(list, intComparator, &searchItem2);

    assert(result1 != NULL); // Item 2 should be found.
    assert(*result1 == searchItem1);
    // assert(result2 == NULL); // Item 5 should not be found.

    // List_first(list);
    // int searchItem3 = 3;
    // int* result3 = (int*)List_search(list, intComparator, &searchItem3);

    // assert(result3 != NULL); // Item 3 should be found.
    // assert(*result3 == searchItem3);

    List_free(list, freeItem);

    printf("All LIST SEARCH test cases passed!\n");
}



bool intComparator(void* pItem, void* pComparisonArg) {
    int item = *(int*)pItem;
    int comparisonArg = *(int*)pComparisonArg;
    return (item == comparisonArg);
}