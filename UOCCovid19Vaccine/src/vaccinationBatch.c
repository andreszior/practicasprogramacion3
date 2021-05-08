#include <stdio.h>
#include <stdio.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "patient.h"
#include "vaccinationBatch.h"
#include "country.h"

// Initialize a vaccine batch
tError vaccinationBatch_init(tVaccineBatch* vb, int id, tVaccine* vac, int num) {
    tError error;

    // Verify pre conditions
    assert(vb != NULL);
    assert(vac != NULL);

    // Allocate the memory for the name string field, using the length of the provided
    // text plus 1 space for the "end of string" char '\0'.
    // To allocate memory we use the malloc command.
    vb->vaccine = (tVaccine*)malloc(sizeof(tVaccine));

    // Check that memory has been allocated.
    // Pointer must be different from NULL.
    if(vb->vaccine == NULL) {
        return ERR_MEMORY_ERROR;
    } else {
        vb->vaccine->name = NULL;
    }

    // Once the memory is allocated, copy the data.
    vb->lotID = id;
    vb->quantity = num;
    error = vaccine_cpy(vb->vaccine, vac);

    // check if any error occured
    if(error != OK)
        return error;

    return OK;
}

// Release memory used by a vaccine batch
void vaccinationBatch_free(tVaccineBatch* vb) {
    // Verify pre conditions
    assert(vb != NULL);

    // All memory allocated with malloc and realloc needs to be freed using the free command.
    // In this case, as we use malloc to allocate the fields, we have to free them
    if(vb->vaccine != NULL) {
        vaccine_free(vb->vaccine);
        free(vb->vaccine);
        vb->vaccine = NULL;
    }

    vb->lotID = 0;
    vb->quantity = 0;
}

// Compare two vaccine batches
bool vaccinationBatch_equals(tVaccineBatch vb1, tVaccineBatch vb2) {
    bool result;

    result = true;
    // To see if two vaccines batches are equal, we need to see if their ids are equal.
    if(vb1.lotID != vb2.lotID) {
        // names are different
        result = false;
    }

    // All fields have the same value
    return result;
}

// Copy a vaccine batch
tError vaccinationBatch_cpy(tVaccineBatch* dest, tVaccineBatch* src) {
    tError error;

    // Verify pre conditions
    assert(dest != NULL);
    assert(src != NULL);

    // free dest vaccine (just in case)
    vaccinationBatch_free(dest);

    // initialize dest with src values.
    error = vaccinationBatch_init(dest, src->lotID, src->vaccine, src->quantity);
    // check if any error occured
    if(error != OK)
        return error;

    return OK;
}

// Create the list
tError vaccinationBatchList_create(tVaccinationBatchList *list) {
    // PR3 EX1
    return ERR_NOT_IMPLEMENTED;
}



// Will return true if list is empty
bool vaccinationBatchList_empty(tVaccinationBatchList list) {
    // PR3 EX1

    return true;
}

// Frees all elements in the list
void vaccinationBatchList_free(tVaccinationBatchList *list) {
    // PR3 EX1
}

// Insert/adds a new Vaccine Batch  to the tVaccinationBatchList
tError vaccineBatchList_insert(tVaccinationBatchList* list, tVaccineBatch vaccineBatch, int index) {
    // PR3_EX1

    return ERR_NOT_IMPLEMENTED;
}

// Deletes a tBestVideoType from the tTopGender list
tError vaccineBatchList_delete(tVaccinationBatchList* list, int index) {
    // PR3_EX1

    return ERR_NOT_IMPLEMENTED;
}

// Gets tVaccinationBatchListNode from given position, NULL if out of bounds
tVaccinationBatchListNode* vaccineBatchList_get(tVaccinationBatchList list, int index) {
    // PR3_EX2

    return NULL;
}

// Duplicate list
tError vaccinationBatchList_duplicate(tVaccinationBatchList *dest, tVaccinationBatchList src) {
    tVaccinationBatchListNode *currNode = NULL;
    tVaccinationBatchListNode *nextNode = NULL;
    tError err;

    // free list (just in case)
    vaccinationBatchList_free(dest);

    // Initialize new list
    err = vaccinationBatchList_create(dest);
    if(err != OK)
        return err;

    // Duplicate the list
    currNode = src.first;
    while(currNode != NULL && err == OK) {
        nextNode = currNode->next;
        err = vaccineBatchList_insert(dest, currNode->e, 0);
        currNode = nextNode;
    }
    return err;
}

// inoculate first vaccine to a patient form a batch list
void vaccineBatchList_inoculate_first_vaccine(tVaccinationBatchList* vbList, tPatient* patient) {
    // PR3 EX2
}

// inoculate second vaccine to a patient form a batch list
void vaccineBatchList_inoculate_second_vaccine(tVaccinationBatchList* vbList, tPatient* patient) {
    // PR3 EX2
}

//  function to explore all batches for inoculate to a patient
void vaccineBatchList_inoculate(tVaccinationBatchList* vbList, tPatient* patient) {
    // PR3 EX2

}

// Sorts input list using quickSort algorithm
void vaccineBatchList_quickSortRecursive(tVaccinationBatchList *list, int low, int high) {
    // PR3_EX3
}

//    The main function for quick sort
tError vaccineBatchList_quicksort(tVaccinationBatchList *queue) {
    // PR3_EX3
    return ERR_NOT_IMPLEMENTED;
}

// Swap two elements in the list
tError vaccineBatchList_swap(tVaccinationBatchList* list, int index_dst, int index_src) {

    assert(list != NULL);
    assert(index_dst >= 0);
    assert(index_src >= 0);
    assert(index_dst < list->size);
    assert(index_src < list->size);

    tError err;
    tVaccinationBatchListNode * node_src, *node_dst;
    tVaccineBatch tmp;

    if(index_dst == index_src) {
        return ERR_INVALID_INDEX;
    }

    tmp.vaccine =  NULL;
    tmp.lotID = 0;
    tmp.quantity = 0;

    node_src = vaccineBatchList_get(*list, index_src);
    node_dst = vaccineBatchList_get(*list, index_dst);

    err = vaccinationBatch_cpy(&tmp, &node_src->e);
    if(err == OK) {
        vaccinationBatch_free(&node_src->e);
        err = vaccinationBatch_cpy(&node_src->e, &node_dst->e);
        if(err == OK) {
            vaccinationBatch_free(&node_dst->e);
            vaccinationBatch_cpy(&node_dst->e, &tmp);
        }
    }

    vaccinationBatch_free(&tmp);

    return err;
}

// Gets lotID from given position, -1 if out of bounds
int vaccineBatchList_getlotID(tVaccinationBatchList list, int index) {

    int i, lotID;
    tVaccinationBatchListNode *prev;

    // Loop until find index position
    i = 0;
    prev = list.first;
    while(i < index && (prev != NULL)) {
        prev = prev->next;
        i++;
    }

    if(prev == NULL) {
        lotID = -1 ;
    } else {
        lotID = prev->e.lotID;
    }

    return lotID;
}

// Helper function - Print a queue in the console - use for debugging
void vaccineBatchList_print(tVaccinationBatchList list) {
    tVaccinationBatchListNode *nodePtr = list.first;;


    while(nodePtr != NULL) {

        printf("%s) lotId %d quantity %d \n", nodePtr->e.vaccine->name, nodePtr->e.lotID, nodePtr->e.quantity);
        nodePtr = nodePtr->next;

    }

    printf("\n");
}
