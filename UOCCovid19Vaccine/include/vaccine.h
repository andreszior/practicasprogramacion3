#ifndef __VACCINE__H__
#define __VACCINE__H__

#include <stdbool.h>
#include "error.h"
#include "commons.h"
#include "country.h"

// vaccine technology enumeration
typedef enum {
	NONE = 0,
    ADENOVIRUSES = 1,
    SARSCOV2 = 2,
    INACTIVE = 3,
    PEPTIDE = 4,
    RNA = 5	
} tVaccineTec;

// vaccine phase enumeration
typedef enum {	
    PRECLINICAL = 0,
    PHASE1 = 1,
    PHASE1_2 = 2,
    PHASE2 = 3,
    PHASE2_3 = 4,
    PHASE3 = 5	
} tVaccinePhase;

// Data type to hold data related to a vaccine
typedef struct {
    char* name;
    tVaccineTec vaccineTec;
    tVaccinePhase vaccinePhase;
    tCountryTable* authCountries;
} tVaccine;

// **** Functions related to tVaccine

// Initialize a vaccine
tError vaccine_init(tVaccine* vac, const char* name, tVaccineTec tec, tVaccinePhase phase);

// Release memory used by a vaccine
void vaccine_free(tVaccine* vac);

// Compare two vaccines
bool vaccine_equals(tVaccine* vac1, tVaccine* vac2);

// Copy a vaccine
tError vaccine_cpy(tVaccine* dest, tVaccine* src);

// Add an authorized country to a vaccine
tError vaccine_add_authorized_country(tVaccine* vac, tCountry* country);

#endif // __VACCINE__H__
