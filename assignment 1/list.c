#include "list.h"
#include <stdlib.h>

// list heads
static List listHeads[LIST_MAX_NUM_HEADS];
// list nodes
static Node listNodes[LIST_MAX_NUM_NODES];

Node* freeNodeList = NULL;
List* freeHeadList = NULL;

// function prototype
void List_initialize();

// if lists are initlizated
static bool init = false;

// Makes a new, empty list, and returns its reference on success. 
// Returns a NULL pointer on failure.
List* List_create(){
    // check if we already init the memory
    if (!init) {
        // init only the first time List_create is called.
        List_initialize();
        init = true;
    }
    // check if no avaible head
    if (freeNodeList == NULL || freeHeadList == NULL) {
        return NULL;  // Handle node or head pool depletion.
    }

    // there is availible head! -> init 
    List* newList = freeHeadList;
    // set new free head for future use
    freeHeadList = freeHeadList->next;
    // init inside list values
    newList->head = NULL;
    newList->current = NULL;
    newList->count = 0;
    newList->used = true;

    // return list reference
    return newList;
};

// Returns the number of items in pList.
int List_count(List* pList){
    // check if client doesnt know what they doing
    assert(pList != NULL);
    return pList->count;
}

// Returns a pointer to the first item in pList and makes the first item the current item.
// Returns NULL and sets current item to NULL if list is empty.
void* List_first(List* pList){
    // check user know what they doing
    assert(pList != NULL);
    // pList is empty
    if(pList->head == NULL){
        pList->current = NULL;

        return NULL;
    }

    // set current to first item
    pList->current = pList->head;
    // return first item
    return pList->current->item;
}

// Returns a pointer to the last item in pList and makes the last item the current item.
// Returns NULL and sets current item to NULL if list is empty.
void* List_last(List* pList){
    // check user know what they doing
    assert(pList != NULL);
    // pList is empty
    if(pList->head == NULL){
        pList->current = NULL;

        return NULL;
    }

    // set current to last
    pList->current = pList->tail;
    // return last item
    return pList->current->item;
}

// Advances pList's current item by one, and returns a pointer to the new current item.
// If this operation advances the current item beyond the end of the pList, a NULL pointer 
// is returned and the current item is set to be beyond end of pList.
void* List_next(List* pList){
    // check user know what they doing
    assert(pList != NULL);
    // check what next item is
    if(pList->current->next == NULL){
        // set current to beyond the end of the list 
        pList->current = LIST_OOB_END;
        return NULL;
    }

    // advance by one
    pList->current = pList->current->next;
    return pList->current;
}

// Backs up pList's current item by one, and returns a pointer to the new current item. 
// If this operation backs up the current item beyond the start of the pList, a NULL pointer 
// is returned and the current item is set to be before the start of pList.
void* List_prev(List* pList){
    // check user know what they doing
    assert(pList != NULL);
    // check if invalid node infront of current node
    if(pList->current->prev == NULL){
        // out of scope
        // set to before the start of pList
        pList->current = LIST_OOB_START;
        return NULL;
    }

    pList->current = pList->current->prev;
    return pList->current;
}

// Returns a pointer to the current item in pList.
void* List_curr(List* pList){
    // check user know what they doing
    assert(pList != NULL);

    // check if List_curr is null
    if(pList->current == NULL){
        // no item to return
        return NULL;
    }

    // return current pointer
    return pList->current->item;
}

// Adds the new item to pList directly after the current item, and makes item the current item. 
// If the current pointer is before the start of the pList, the item is added at the start. If 
// the current pointer is beyond the end of the pList, the item is added at the end. 
// Returns 0 on success, -1 on failure.
int List_insert_after(List* pList, void* pItem){
    // check user know what they doing
    assert(pList != NULL);
    // check if current is before the start (insert at start)
     if(pList->current == LIST_OOB_START || pList->current == NULL){
        Node* newNode = freeNodeList;
        // check if node was already statically allocated
        if(newNode == NULL){
            // no new node can be allocated -> fail insertion
            return -1;
        }
        freeNodeList = freeNodeList->next;

        // init node
        newNode->used = true;
        newNode->item = pItem;
        newNode->next = NULL;
        // since new node is at the start it is head now?
        pList->head = newNode;

        // make new item current
        pList->current = newNode;

        pList->tail = newNode;

        // increase count 
        pList->count++;
        // success
        return 0;        
    } else if(pList->current == LIST_OOB_END){ // current is beyond list add at end

        Node* newNode = freeNodeList;
        // check if node was already statically allocated
        if(newNode == NULL){
            // no new node can be allocated -> fail insertion
            return -1;
        }

        freeNodeList = freeNodeList->next;

        // init node
        newNode->used = true;
        newNode->item = pItem;
        newNode->next = NULL;
        newNode->prev = pList->tail;

        pList->tail = newNode;

        // make new item current
        pList->current = newNode;
         // increase count 
        pList->count++;
        // success
        return 0; 
    } else if(pList->current == pList->head){
        Node* newNode = freeNodeList;
        // check if node was already statically allocated
        if(newNode == NULL){
            // no new node can be allocated -> fail insertion
            return -1;
        }

        freeNodeList = freeNodeList->next;

        // init node
        newNode->used = true;
        newNode->item = pItem;
        newNode->prev = pList->current;
        
        // set newNode before current
        pList->current->next = newNode;

        pList->current = newNode;
        pList->head = newNode;

        // increase count 
        pList->count++;
        // success
        return 0;
    }

    // last case: current exists and its somewhere in the bounds of linked list
    if(pList->current != NULL){
        Node* newNode = freeNodeList;
        // check if node was already statically allocated
        if(newNode == NULL){
            // no new node can be allocated -> fail insertion
            return -1;
        }

        freeNodeList = freeNodeList->next;

        // init node
        newNode->used = true;
        newNode->item = pItem;
        newNode->next = NULL;
        
        // set newNode after current (both ways)
        pList->current->next = newNode;
        newNode->prev = pList->current;
        // increase count 
        pList->count++;
        // success
        return 0;
    }

}

// Adds item to pList directly before the current item, and makes the new item the current one. 
// If the current pointer is before the start of the pList, the item is added at the start. 
// If the current pointer is beyond the end of the pList, the item is added at the end. 
// Returns 0 on success, -1 on failure.
int List_insert_before(List* pList, void* pItem){
 // check user know what they doing
    assert(pList != NULL);
    // check if current is before the start (insert at start)
    if(pList->current == LIST_OOB_START || pList->current == NULL){
        Node* newNode = freeNodeList;
        // check if node was already statically allocated
        if(newNode == NULL){
            // no new node can be allocated -> fail insertion
            return -1;
        }
        freeNodeList = freeNodeList->next;

        // init node
        newNode->used = true;
        newNode->item = pItem;
        newNode->next = NULL;
        // since new node is at the start it is head now?
        pList->head = newNode;

        // make new item current
        pList->current = newNode;

        pList->tail = newNode;

        // increase count 
        pList->count++;
        // success
        return 0;        
    } else if(pList->current == LIST_OOB_END){ // current is beyond list add at end

        Node* newNode = freeNodeList;
        // check if node was already statically allocated
        if(newNode == NULL){
            // no new node can be allocated -> fail insertion
            return -1;
        }

        freeNodeList = freeNodeList->next;

        // init node
        newNode->used = true;
        newNode->item = pItem;
        newNode->next = NULL;
        newNode->prev = pList->tail;

        pList->tail = newNode;

        // make new item current
        pList->current = newNode;
         // increase count 
        pList->count++;
        // success
        return 0; 
    } else if(pList->current == pList->head){
        Node* newNode = freeNodeList;
        // check if node was already statically allocated
        if(newNode == NULL){
            // no new node can be allocated -> fail insertion
            return -1;
        }

        freeNodeList = freeNodeList->next;

        // init node
        newNode->used = true;
        newNode->item = pItem;
        newNode->next = pList->current;
        
        // set newNode before current
        pList->current->prev = newNode;

        pList->current = newNode;
        pList->head = newNode;

        // increase count 
        pList->count++;
        // success
        return 0;
    }

    // last case: current exists and its somewhere in the bounds of linked list
    //Adds item to pList directly before the current item, and makes the new item the current one. 
    if(pList->current != NULL){
        Node* newNode = freeNodeList;
        // check if node was already statically allocated
        if(newNode == NULL){
            // no new node can be allocated -> fail insertion
            return -1;
        }

        freeNodeList = freeNodeList->next;

        // init node
        newNode->used = true;
        newNode->item = pItem;
        newNode->next = pList->current;
        
        // set newNode before current
        pList->current->prev = newNode;

        pList->current = newNode;

        // increase count 
        pList->count++;
        // success
        return 0;
    }
}

// Adds item to the end of pList, and makes the new item the current one. 
// Returns 0 on success, -1 on failure.
int List_append(List* pList, void* pItem){
    assert(pList != NULL);

    Node* newNode = freeNodeList;
    if (newNode == NULL) {
        return -1;  
    }
    freeNodeList = freeNodeList->next;

    newNode->used = true;
    newNode->item = pItem;
    newNode->next = NULL;

    if (pList->tail != NULL) {
        pList->tail->next = newNode;
        newNode->prev = pList->tail;
    } else {
        pList->head = newNode;
    }

    pList->tail = newNode;
    pList->current = newNode;
    pList->count++;

    // success
    return 0;
}

// Adds item to the front of pList, and makes the new item the current one. 
// Returns 0 on success, -1 on failure.
int List_prepend(List* pList, void* pItem){
    assert(pList != NULL);
    
    Node* newNode = freeNodeList;
    if (newNode == NULL) {
        return LIST_FAIL;  
    }
    freeNodeList = freeNodeList->next;

    newNode->used = true;
    newNode->item = pItem;
    newNode->next = pList->head;
    newNode->prev = NULL;

    if (pList->head != NULL) {
        pList->head->prev = newNode;
    } else {
        pList->tail = newNode;
    }

    pList->head = newNode;
    pList->current = newNode;
    pList->count++;

    // success
    return 0;
}

// Return current item and take it out of pList. Make the next item the current one.
// If the current pointer is before the start of the pList, or beyond the end of the pList,
// then do not change the pList and return NULL.
void* List_remove(List* pList){
    assert(pList != NULL);

    if (pList->current == LIST_OOB_START || pList->current == LIST_OOB_END || pList->current == NULL){
        return NULL;
    }

    Node* current = pList->current;
    void* currentItem = current->item;

    if(pList->current == pList->tail || pList->head == pList->tail){
        return List_trim(pList);
    }
    
    // Normal condition
    // link currents prev and  next node to each other to get rid of current
    if(pList->current->prev != NULL){
        pList->current->prev->next = pList->current->next;
    } else {
        // means current is head
        // set new head to current->next
        pList->head = pList->current->next;
    }

    if(pList->current->next != NULL){
        pList->current->next->prev = pList->current->prev;
    } else {
        // means current is tail
        // set new tail to current -> prev
        pList->tail = pList->current->prev;
    }

    // de init the current node;
    pList->current->used = false;
    pList->current->prev = NULL;
    pList->current->item = NULL;
    pList->current->prev = NULL;

    // connect back to the free node list 
    pList->current->next = freeNodeList;

    // put back on top of free list
    freeNodeList = pList->current;

    //TODO: double check this is right
    

    // derease count of list
    pList->count--;

    return currentItem;

}

// Return last item and take it out of pList. Make the new last item the current one.
// Return NULL if pList is initially empty.
void* List_trim(List* pList){
    if (pList == NULL || pList->tail == NULL) {
        return NULL; 
    }

    Node* lastNode = pList->tail;
    void* lastItem = lastNode->item;

    if (pList->tail->prev != NULL) {
        pList->tail->prev->next = NULL;
        pList->tail = pList->tail->prev;
        pList->current = pList->tail;
    } else {
        pList->head = NULL;
        pList->tail = NULL;
        pList->current = NULL;
    }

    // de init node 
    lastNode->used = false;
    lastNode->item = NULL;
    lastNode->next = freeNodeList;
    lastNode->prev = NULL;
    freeNodeList = lastNode;

    
    pList->count--;

    return lastItem;
}

// Adds pList2 to the end of pList1. The current pointer is set to the current pointer of pList1. 
// pList2 no longer exists after the operation; its head is available
// for future operations.
void List_concat(List* pList1, List* pList2){
    assert(pList1 != NULL);
    assert(pList2 != NULL);

    if(pList2->count == 0){
        // nothing in list
        return;
    }

    // pList1 is empty
    if(pList1->count == 0){
        pList1->head = pList2->head;
        pList1->tail = pList2->tail;
        pList1->current = pList2->current;
    } else {
        // concancate
        // connect tail to head
        if (pList1->tail != NULL) {
            pList1->tail->next = pList2->head;
        }
        // Connect head to tail.
        if (pList2->head != NULL) {
            pList2->head->prev = pList1->tail;
        }

        // same tails
        pList1->tail = pList2->tail;
    }

    pList1->count += pList2->count;

    // delete pList2 content
    if (pList2->head != NULL) {
        pList2->head->next = freeHeadList;
        freeHeadList = pList2->head;
    }
    pList2->head = NULL;
    pList2->tail = NULL;
    pList2->current = NULL;
    pList2->count = 0;
    pList2->used = false;
}


// Delete pList. pItemFreeFn is a pointer to a routine that frees an item. 
// It should be invoked (within List_free) as: (*pItemFreeFn)(itemToBeFreedFromNode);
// pList and all its nodes no longer exists after the operation; its head and nodes are 
// available for future operations.
typedef void (*FREE_FN)(void* pItem);
void List_free(List* pList, FREE_FN pItemFreeFn){
    assert(pList != NULL);

     if (pList == NULL) {
        return; // Handle invalid list.
    }

    // Free all nodes in the list.
    Node* currentNode = pList->head;
    while (currentNode != NULL) {
        Node* nextNode = currentNode->next;

        // Call the item freeing function if provided.
        if (pItemFreeFn != NULL && currentNode->item != NULL) {
            (*pItemFreeFn)(currentNode->item);
        }

        if(currentNode = pList->head){
            currentNode->next = freeHeadList;
            currentNode->item = NULL;
            freeHeadList = currentNode;

            currentNode = nextNode;
        } else {
            // Reset the node and return it to the free node list.
            currentNode->next = freeNodeList;
            currentNode->item = NULL;
            freeNodeList = currentNode;

            currentNode = nextNode;
        }
    }

    // Reset the list properties.
    pList->head = NULL;
    pList->tail = NULL;
    pList->current = NULL;
    pList->count = 0;
    pList->used = false;

    // Return the list head to the free head list.
    if (pList != freeHeadList) {
        pList->next = freeHeadList;
        freeHeadList = pList;
    }
}


// private functions 
void List_initialize() {
    for (int i = 0; i < LIST_MAX_NUM_HEADS; i++) {
        listHeads[i].head = NULL;
        listHeads[i].tail = NULL;
        listHeads[i].current = NULL;
        listHeads[i].count = 0;
    }

    for (int i = 0; i < LIST_MAX_NUM_NODES; i++) {
        listNodes[i].used = false;
        listNodes[i].next = freeNodeList;
        freeNodeList = &listNodes[i];
    }

    for (int i = 0; i < LIST_MAX_NUM_HEADS; i++) {
        listHeads[i].used = false;
        listHeads[i].next = freeHeadList;
        freeHeadList = &listHeads[i];
    }
};

// Search pList, starting at the current item, until the end is reached or a match is found. 
// In this context, a match is determined by the comparator parameter. This parameter is a
// pointer to a routine that takes as its first argument an item pointer, and as its second 
// argument pComparisonArg. Comparator returns 0 if the item and comparisonArg don't match, 
// or 1 if they do. Exactly what constitutes a match is up to the implementor of comparator. 
// 
// If a match is found, the current pointer is left at the matched item and the pointer to 
// that item is returned. If no match is found, the current pointer is left beyond the end of 
// the list and a NULL pointer is returned.
// 
// If the current pointer is before the start of the pList, then start searching from
// the first node in the list (if any).
typedef bool (*COMPARATOR_FN)(void* pItem, void* pComparisonArg);
void* List_search(List* pList, COMPARATOR_FN pComparator, void* pComparisonArg){
    assert(pList != NULL);

    Node* currentNode = pList->current;

    if (currentNode == LIST_OOB_START) {
        currentNode = pList->head;
    }

    // search
    while (currentNode != NULL) {
        if ((*pComparator)(currentNode->item, pComparisonArg)) {
            // found match
            pList->current = currentNode;
            return currentNode->item;
        }
        currentNode = currentNode->next;
    }

    // No match found, set current pointer beyond the end of the list and return NULL.
    pList->current = LIST_OOB_END;
    return NULL;
}