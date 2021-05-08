#ifndef __COUNTRY__H__
#define __COUNTRY__H__

#include <stdbool.h>
#include "error.h"
#include "commons.h"

// Data type to hold data related to a Country
typedef struct {   
    bool isEU; 
	char* name;
} tCountry;

// Table of tCountry elements
typedef struct {
    unsigned int size;

    // Using static memory, the elements is an array of a fixed length MAX_ELEMENTS.
    // That means that we are using the same amount of memory when the table is empty and
    // when is full. We cannot add more elements than MAX_ELEMENTS.
    // tCountry elements[MAX_ELEMENTS];

    // Using dynamic memory, the elements is a pointer to a region of memory.
    // Initially, we have no memory (NULL), and we need to allocate memory
    // when we want to add elements. We can add as many elements as we want,
    // the only limit is the total amount of memory of our computer.
    tCountry* elements;
} tCountryTable;

// **** Functions related to management of tCountry objects

// Initialize a country object
tError country_init(tCountry* country, const char* name, bool isEU);

// Release memory used by country object
void country_free(tCountry* object);

// Compare two country objects
bool country_equals(tCountry* country1, tCountry* country2);

// Copy the data of a country to another country
tError country_cpy(tCountry* dest, tCountry* src);

// **** Functions related to management of tCountryTable objects

// Initialize the Table of countries
void countryTable_init(tCountryTable* table);

// Release the memory used by countryTable structure
void countryTable_free(tCountryTable* table);

// Add a new country to the table
tError countryTable_add(tCountryTable* table, tCountry* country);

// Remove a country from the table
tError countryTable_remove(tCountryTable* table, tCountry* country);

// Get country by name
tCountry* countryTable_find(tCountryTable* table, const char* name);

// Get the size of the table
unsigned int countryTable_size(tCountryTable* table);

// Copy the data of a country to another country
tError countryTable_cpy(tCountryTable* dest, tCountryTable* src);

#endif // __COUNTRY__H__
