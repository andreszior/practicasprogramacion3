#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <ctype.h>
#include "country.h"

// **** Functions related to management of tCountry objects

// Initialize a country
tError country_init(tCountry* country, const char* name, bool isEU) {
    // Verify pre conditions
    assert(country != NULL);
    assert(name != NULL);

    // Allocate the memory for all the fields, using the length of the provided
    // text plus 1 space for the "end of string" char '\0'.
    // To allocate memory we use the malloc command.
    country->name = (char*)malloc((strlen(name) + 1) * sizeof(char));

    // Check that memory has been allocated for all fields.
    // Pointer must be different from NULL.
    if(country->name == NULL) {
        // Some of the fields have a NULL value, what means that we found
        // some problem allocating the memory
        return ERR_MEMORY_ERROR;
    }

    // Once the memory is allocated, copy the data. As the fields are strings,
    // we need to use the string copy function strcpy.
    strcpy(country->name, name);

    // Initialize the rest of fields
    country->isEU = isEU;

    return OK;
}

// Release memory used by country object
void country_free(tCountry* object) {
    // Verify pre conditions
    assert(object != NULL);

    // All memory allocated with malloc and realloc needs to be freed using the free command.
    // In this case, as we use malloc to allocate the fields, we have to free them
    if(object->name != NULL) {
        free(object->name);
        object->name = NULL;
    }
}

// Compare two country objects
bool country_equals(tCountry* country1, tCountry* country2) {
    // Verify pre conditions
    assert(country1 != NULL);
    assert(country2 != NULL);

    // To see if two countries are equals, usually we need to see ALL the values for their fields are equals.
    // On this case, we can consider name as key identifier and compare only this value

    // Strings are pointers to a table of chars, therefore, cannot be compared  as
    // " country1->name == country2->name ". We need to use a string comparison function

    if(strcmp(country1->name, country2->name) != 0) {
        // Countries are different
        return false;
    }

    // All fields have the same value
    return true;
}

// Copy the data of a country to another country
tError country_cpy(tCountry* dest, tCountry* src) {
    tError error;

    // Verify pre conditions
    assert(dest != NULL);
    assert(src != NULL);

    // Just in case, free space used by destination object.
    country_free(dest);

    // Initialize the element with the new data
    error = country_init(dest, src->name, src->isEU);
    if(error != OK)
        return error;

    return OK;
}

// **** Functions related to management of tCountryTable objects

// Initialize the table of countries
void countryTable_init(tCountryTable* table) {
    // Verify pre conditions
    assert(table != NULL);

    // The initialization of a table is to set it to the empty state.
    // That is, with 0 elements.
    table->size = 0;
    // Using dynamic memory, the pointer to the elements
    // must be set to NULL (no memory allocated).
    table->elements = NULL;
}

// Release the memory used by countryTable structure
void countryTable_free(tCountryTable* table) {
    int i;

    // Verify pre conditions
    assert(table != NULL);

    // All memory allocated with malloc and realloc needs to be freed using the free command. In this case, as we use malloc/realloc to allocate the elements, and need to free them.
    if(table->elements != NULL) {
        for(i = 0; i < table->size; i++) {
            country_free(&table->elements[i]);
        }
        free(table->elements);
        table->elements = NULL;
        // As the table is now empty, assign the size to 0.
        table->size = 0;
    }
}

// Add a new country to the table
tError countryTable_add(tCountryTable* table, tCountry* country) {
    tCountry* elementsAux;
    tError error;

    // Verify pre conditions
    assert(table != NULL);
    assert(country != NULL);

    // Check if the element is already on the table
    if(countryTable_find(table, country->name))
        return ERR_DUPLICATED;

    // The first step is to allocate the required space.
    // There are two methods to manage the
    // memory (malloc and realloc). Malloc allows
    // to allocate a new memory block, while realloc
    // allows to modify an existing memory block.
    if(table->size == 0) {  // Empty table
        // Since the table is empty, and we do not have any previous memory block,
        // we have to use malloc. The amount of memory we need is the number of
        // elements (will be 1) times the size of one element, which is computed
        // by sizeof(type). In this case the type is tCountry.
        elementsAux = (tCountry*)malloc((table->size + 1) * sizeof(tCountry));

        // Check that the memory has been allocated
        if(elementsAux == NULL) {
            // Error allocating or reallocating the memory
            return ERR_MEMORY_ERROR;
        } else {
            table->elements = elementsAux;
            // set the table size to one
            table->size = 1;
        }
    } else { // table with elements
        // Since the table is not empty, we already have a memory block.
        // We need to modify the size of this block, using the realloc command.
        // The amount of memory we need is the number of elements times
        // the size of one element, which is computed by sizeof(type).
        // In this case the type is tCountry. We provide the previous block of memory.
        elementsAux = (tCountry*)realloc(table->elements, (table->size + 1) * sizeof(tCountry));
        // Check that the memory has been allocated
        if(elementsAux == NULL) {
            // Error allocating or reallocating the memory
            return ERR_MEMORY_ERROR;
        } else {
            table->elements = elementsAux;
            // Increase the number of elements of the table
            table->size = table->size + 1;
        }
    }

    // Once we have the block of memory, which is an array of tCountry elements,
    // we initialize the new element (which is the last one). The last element
    // is " table->elements[table->size - 1] " (we start counting at 0)
    error = country_init(&(table->elements[table->size - 1]), country->name, country->isEU);
    if(error != OK)
        return error;

    return OK;
}

// Remove a country from the table
tError countryTable_remove(tCountryTable* table, tCountry* country) {
    bool found;
    int i;
    tCountry* elementsAux;

    // Verify pre conditions
    assert(table != NULL);
    assert(country != NULL);

    // To remove an element of a table, we will move all elements after this element one position,
    // to fill the space of the removed element.
    found = false;
    for(i = 0; i < table->size; i++) {
        // If the element has been found. Displace this element to the previous element
        // (will never happend for the first one). We use the ADDRESS of the previous element &(table->elements[i-1])
        // as destination, and ADDRESS of the current element &(table->elements[i]) as source.
        if(found) {
            // Check the return code to detect memory allocation errors
            if(country_cpy(&(table->elements[i - 1]), &(table->elements[i])) == ERR_MEMORY_ERROR) {
                // Error allocating memory. Just stop the process and return memory error.
                return ERR_MEMORY_ERROR;
            }
        } else
            if(country_equals(&table->elements[i], country)) {
                // The current element is the element we want to remove. Set found flag to true to start element movement.
                found = true;
            }
    }

    // Once removed the element, we need to modify the memory used by the table.
    if(found) {
        // If we are removing the last element, we will free
        // the last/remaining element in table / assign pointer
        // to NULL
        if(table->size <= 1) {
            countryTable_free(table);
        } else {
            country_free(&table->elements[table->size - 1]);
            // Modify the used memory. As we are modifying a previously
            // allocated block, we need to use the realloc command.
            elementsAux = (tCountry*)realloc(table->elements, (table->size - 1) * sizeof(tCountry));

            // Check that the memory has been allocated
            if(elementsAux == NULL) {
                // Error allocating or reallocating the memory
                return ERR_MEMORY_ERROR;
            } else {
                table->elements = elementsAux;
                // Succesfully allocated, set new table size
                table->size = table->size - 1;
            }
        }
    } else {
        // If the element was not in the table, return an error.
        return ERR_NOT_FOUND;
    }

    return OK;
}

// Get country by name
tCountry* countryTable_find(tCountryTable* table, const char* name) {
    int i;

    // Verify pre conditions
    assert(table != NULL);
    assert(name != NULL);

    // Search over the table and return once we found the element.
    for(i = 0; i < table->size; i++) {
        if(strcmp(table->elements[i].name, name) == 0) {
            // We return the ADDRESS (&) of the element, which is a pointer to the element
            return &(table->elements[i]);
        }
    }

    // The element has not been found. Return NULL (empty pointer).
    return NULL;
}

// Get the size of the table
unsigned int countryTable_size(tCountryTable* table) {
    // Verify pre conditions
    assert(table != NULL);

    // The size of the table is the number of elements. This value is stored in the "size" field.
    return table->size;
}

// Copy the data of a country to another country
tError countryTable_cpy(tCountryTable* dest, tCountryTable* src) {
    int i;
    tError error;

    // Verify pre conditions
    assert(dest != NULL);
    assert(src != NULL);

    // free dest (just in case)
    countryTable_free(dest);

    // initialize dest
    countryTable_init(dest);

    // add countries from src to dest
    for(i = 0; i < src->size; i++) {
        error = countryTable_add(dest, &src->elements[i]);
        if(error != OK)
            return error;
    }

    return OK;
}
