#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "vaccine.h"

// Initialize a vaccine
tError vaccine_init(tVaccine* vac, const char* name, tVaccineTec tec, tVaccinePhase phase) {
    // PR1 EX2

    //Declare preconditions
    assert(vac != NULL);
    assert(name != NULL);

    //allocate memory for this var 
    vac->name = (char*)malloc((strlen(name) + 1) * sizeof(char));

    //check if we have enough memory for allocating all the information
    if (vac->name == NULL) {
        
        return ERR_MEMORY_ERROR;
    }
    //Copy of the data
    strcpy(vac->name, name);
    /* MIRAR QUE COÑO HACER CON ESTE RETURN de abajo.
     return ERR_NOT_IMPLEMENTED;*/ 

    //initialize the rest of var
    vac->vaccineTec = 0;
    vac->vaccinePhase = 0;

    //ionitialize table
    vac->authCountries = 0;

    return OK;
}

// Release memory used by a vaccine
void vaccine_free(tVaccine* vac) {
    // PR1 EX2
    //declare preconditions
    assert(vac != NULL);
    if (vac != NULL) {
        free(vac->name);
        free(vac->vaccinePhase);
        free(vac->vaccineTec);
        free(vac->authCountries);
        
        vac->name = NULL;
        vac->authCountries = NULL;
        vac->vaccinePhase = NULL;
        vac->vaccineTec = NULL;
    }
}

// Compare two vaccines
bool vaccine_equals(tVaccine* vac1, tVaccine* vac2) {
    // PR1 EX2
    // declare preconditions
    assert(vac1 != NULL);
    assert(vac2 != NULL);

    if (strcmp(vac1->name, vac2->name) != 0) {
        return false;
    }

    return true;
}

// Copy a vaccine
tError vaccine_cpy(tVaccine* dest, tVaccine* src) {
    // PR1 EX2
    tError error;
    int i;

    assert(dest != NULL);
    assert(src != NULL);

    countryTable_free(dest);

    countryTable_init(dest);

    for(i = 0; i < src->size; i++) {
        error = countryTable_add(dest, &src->authCountries->elements[i]);
        if(error != OK)
            return error;
    }

    return OK;
    /*return ERR_NOT_IMPLEMENTED; */
}

// Add an authorized country to a vaccine
tError vaccine_add_authorized_country(tVaccine* vac, tCountry* country) {
    // PR1 EX2
    tVaccine* auxVac;
    tError error;
    //Declare preconditions
    assert(vac != NULL);
    assert(country != NULL);

    //Check if the country has the vac authorized already
    if (countryTable_find(vac->authCountries, country->name))
    {
        return ERR_DUPLICATED;
    }
    // we must allocate space for the new vac
    if (vac->authCountries == 0) {
        auxVac = (tVaccine*)malloc((vac->authCountries->size + 1) * sizeof(tVaccine));

        //check again 
        if (auxVac == NULL) {
            return ERR_MEMORY_ERROR
        } else {
            vac->authCountries = auxVac; 
        }
         
    } else {
        auxVac = (tVaccine*)realloc(vac->authCountries->elements, (vac->authCountries->size + 1) * sizeof(tCountry));
        //check if the memory is allocated
        if (auxVac == NULL) {
            return ERR_MEMORY_ERROR
        } else {
           vac->authCountries->elements = auxVac;
           vac->authCountries->size + 1; 
        }
        
    }
    error = vaccine_init(&(vac->authCountries->elements[vac->authCountries->size - 1], vac->name, vac->vaccineTec, vac->vaccinePhase));
    if (error != OK) {
        return ERR_NOT_IMPLEMENTED;
    }

    return OK;
}
