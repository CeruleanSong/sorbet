#include "system.h"

/*****************************************************
 * ENUMERATIONS
 *****************************************************/

/*****************************************************
 * TYPE DECLARATIONS
 *****************************************************/

/*****************************************************
 * TYPE IMPLEMENTATIONS
 *****************************************************/

/*****************************************************
 * FUNCTION DECLARATIONS
 *****************************************************/

/*****************************************************
 * FUNCTION IMPLEMENTATIONS
 *****************************************************/

SYSTEM_T* system__create(void (*func))
{
	SYSTEM_T* system = malloc(sizeof(SYSTEM_T));
	if(!system) {
		// TODO: logging
		return NULL;
	}

	system->system_id = NULL;
	system->func = func;

	for(ECS__COLLECTION_SIZE_T i = 0; i < ECS__COLLECTION_MAX; i++) {
		system->table[i] = NULL;
	}

	return system;
} // system__create()