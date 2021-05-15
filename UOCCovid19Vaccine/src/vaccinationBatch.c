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

void freeSpace(tVaccinationBatchListNode* node) { 
	tVaccinationBatchListNode *temp = NULL;
	

	while(node != NULL) {
		temp = node->next;
		free(node);
		node = temp;
	}
	
	node = NULL;
}

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
	//check pre-conditions
	assert(list != NULL);
	
	//assign pointers to null
	list->first = NULL;
	list->last = NULL;
	list->size = 0;
	
	return OK;
}



// Will return true if list is empty
bool vaccinationBatchList_empty(tVaccinationBatchList list) {
    // PR3 EX1
	//check if there are elements in the list
	if (list.first != NULL || list.size != 0){
		return false;
	}
	return true;
}
tError initElement(tVaccinationBatchListNode* node, tVaccineBatch vaccineBatch) {
	
	tError err;
	vaccinationBatch_free(&node->e);
	err = vaccinationBatch_cpy(&node->e, &vaccineBatch);
	if (err < 0) 
		return ERR_MEMORY_ERROR;
	 
	return OK;
}
// Frees all elements in the list
void vaccinationBatchList_free(tVaccinationBatchList *list) {
    // PR3 EX1
	//check pre-conditions
	assert(list != NULL);
	tVaccinationBatchListNode *tmp = NULL;
	tmp = (tVaccinationBatchListNode*)malloc(sizeof(tVaccinationBatchListNode));
	
	//Iterate the elementes in the list
	while(!vaccinationBatchList_empty(*list)){
		tmp = list->first->next;
		vaccinationBatch_free(&list->first->e);
		free(list->first);
		list->first = tmp;
		list->size--;
	}
	
	//check post-conditions
	assert(list->first == NULL);
	assert(list->last == NULL);
	
}
//aux function for getting previous node in the list
tVaccinationBatchListNode* vaccineBatchList_getPrevious(tVaccinationBatchList* list, int index) {
	int i;
	tVaccinationBatchListNode* prev;
	
	i = 0;
	prev = list->first;
	while (i < index && (prev != NULL)) {
		prev = prev->next;
		i = i+1;
	}
	return prev;
}



// Insert/adds a new Vaccine Batch  to the tVaccinationBatchList
tError vaccineBatchList_insert(tVaccinationBatchList* list, tVaccineBatch vaccineBatch, int index) {
    // PR3_EX1
	
	//check preconditions
	assert(list != NULL);
	assert(vaccineBatch.vaccine != NULL);
	
	//declare variables
	tVaccinationBatchListNode *tmp = NULL;
	tVaccinationBatchListNode *newNode = NULL;
	
	//Get memory for the aux variables
	if (index > list->size) {
		return ERR_MEMORY_ERROR;
	} else if (index <= list->size) {
		newNode = (tVaccinationBatchListNode*)malloc(sizeof(tVaccinationBatchListNode));	
		//check if the memory has been allocated
		if (newNode == NULL) {
			return ERR_MEMORY_ERROR;
		} else {
			newNode->e.vaccine =  NULL;
			newNode->e.lotID = 0;
			newNode->e.quantity = 0;
			if (initElement(newNode, vaccineBatch) < 0) {
				freeSpace(newNode);
				free(newNode);
			} else {
				if (index == 0) {
					newNode->next = list->first;
					list->first = newNode;
				} else {
					tmp = vaccineBatchList_get(*list, index - 1);
					if (tmp != NULL) {
						newNode->next = tmp->next;
						tmp->next = newNode;
					} else {
						free(newNode);
						newNode = NULL;	
					}
				}
				//Update size list
				list->size++;
				
				//Update position
				if (index ==list->size){
					list->last = newNode;
				}
			}
				
		}
		//return OK;
	}
	return OK;
}

// Deletes a tBestVideoType from the tTopGender list
tError vaccineBatchList_delete(tVaccinationBatchList* list, int index) {
    // PR3_EX1
	
	//check pre-conditions
	//assert(list != NULL);
	
	//declare variables
	tVaccinationBatchListNode *tmp = NULL;
	tVaccinationBatchListNode *del = NULL;
	tmp = (tVaccinationBatchListNode*)malloc(sizeof(tVaccinationBatchListNode));
	
	if (index > list->size - 1) {
		return ERR_INVALID_INDEX;
	} else if (vaccinationBatchList_empty(*list) == true) {
		return ERR_EMPTY_LIST;
	} else if (index == 0) {
		tmp = list->first->next;
		vaccinationBatch_free(&list->first->e);
		free(list->first);
		list->first = tmp;
	} else {
		//del->e.vaccine =  NULL;
		//del->e.lotID = 0;
		//del->e.quantity = 0;
		del = vaccineBatchList_getPrevious(list, index - 1);
		if (del != NULL) {
			tmp = del->next;
			if (tmp == NULL) {
				return ERR_INVALID_INDEX;
			} else {
				del->next = tmp->next;
			}
		} else {
			return ERR_INVALID_INDEX;
		}
	}
		list->size--;
		
		if (list->size == 0) {
			list->last = vaccineBatchList_get(*list, list->size);
		} else {
			list->last = NULL;
		}
		//FREE MEMORY
		free(tmp);
		return OK;
}

// Gets tVaccinationBatchListNode from given position, NULL if out of bounds
tVaccinationBatchListNode* vaccineBatchList_get(tVaccinationBatchList list, int index) {
    // PR3_EX2
	//check pre-conditions
	//assert(list.first != NULL);
	//declare variables
	tVaccinationBatchListNode *currentNode;
	
	//Allocate memory
	currentNode = vaccineBatchList_getPrevious(&list, index);
	if (currentNode == NULL) {
		return NULL;
	} else {
		return currentNode;
	}
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
