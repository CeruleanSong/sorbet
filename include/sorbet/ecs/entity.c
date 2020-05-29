#include "entity.h"

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

ENTITY_T* entity__create(ECS__COMPONENT_BIT_T components, void* payload)
{
	ENTITY_T* entity = malloc(sizeof(ENTITY_T));
	if(!entity) {
		// TODO: logging
		return NULL;
	}

	entity->status = DISABLED;
	entity->components = components;
	entity->entity_id = NULL;
	entity->payoad = payload;
	
	return entity;
} // ENTITY_T* entity__create()
