#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <ctype.h>
#include <stdio.h>
#include "developer.h"

// **** Functions related to management of tDeveloper objects

// Initialize a developer object
tError developer_init(tDeveloper* dev, const char* name, tCountry* country, tVaccine* vaccine) {
    // PR1 EX3

    return ERR_NOT_IMPLEMENTED;
}

// Release memory used by developer object
void developer_free(tDeveloper* object) {
    // PR1 EX3
   
}

// Compare two developer objects
bool developer_equals(tDeveloper* dev1, tDeveloper* dev2) {
    // PR1 EX3

    return false;
}

// Copy the data of a developer to another developer
tError developer_cpy(tDeveloper* dest, tDeveloper* src) {
    // PR1 EX3

     return ERR_NOT_IMPLEMENTED;
}


// **** Functions related to management of tDeveloperTable objects

// Initialize the table of developers
void developerTable_init(tDeveloperTable* table) {
    // PR1 EX3

}

// Release the memory used by tDeveloperTable structure
void developerTable_free(tDeveloperTable* table) {
    // PR1 EX3

}

// Add a new developer to the table
tError developerTable_add(tDeveloperTable* table, tDeveloper* dev) {
    // PR1 EX3

     return ERR_NOT_IMPLEMENTED;
}

// Remove a developer from the table
tError developerTable_remove(tDeveloperTable* table, tDeveloper* dev) {
    // PR1 EX3

     return ERR_NOT_IMPLEMENTED;
}

// Returns the number of tDeveloper that have an authorized vaccine in at least one country
int developerTable_num_authorized(tDeveloperTable* table) {
    // PR1 EX3

	return ERR_NOT_IMPLEMENTED;
}

// Returns the position of the tDeveloper table with the vaccine that has more countries that
// authorize it, in case of a tie it would select the first one in the table.
int developerTable_most_popular(tDeveloperTable* table) {
    // PR1 EX3
    
    return ERR_NOT_FOUND;;
}

// Given a tDeveloper find the position it occupies in the tDevelope table
int developerTable_find(tDeveloperTable* table, tDeveloper* dev) {
    // PR1 EX3

    int i;

    // Verify pre conditions
    assert(table != NULL);
    assert(dev != NULL);

    // Search over the table and return once we found the element.
    for(i = 0; i < table->size; i++) {
        if(developer_equals(&table->elements[i], dev)) {
            // Return the position of the element
            return i;
        }
    }

    // The element has not been found. Return ERR_NOT_FOUND.
    return ERR_NOT_FOUND;
}

// Get the size of the table
unsigned int developerTable_size(tDeveloperTable* table)  {
    // Verify pre conditions
    assert(table != NULL);

    // The size of the table is the number of elements. This value is stored in the "size" field.
    return table->size;
}

// Prints basic information from the tDeveloper table on the screen
void developerTable_print(tDeveloperTable* table) {
    int i;

    // Verify pre conditions
    assert(table != NULL);

    for(i = 0; i < table->size; i++) {
        developer_print(&table->elements[i]);
    }
    printf("\n");
}

// prints basic information from the tDeveloper on the screen
void developer_print(tDeveloper* dev) {
    // Verify pre conditions
    assert(dev != NULL);

    printf("%s %s %s\n", dev->name, dev->country->name, dev->vaccine->name);
}
