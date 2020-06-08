#ifndef ECS_COMPONENT_H
#define ECS_COMPONENT_H

#include "../types.h"
#include "../set/queue.h"

#include "entity.h"

typedef struct SYSTEM SYSTEM_T;
typedef struct ENTITY ENTITY_T;

/*****************************************************
 * ENUMERATIONS
 *****************************************************/

/*****************************************************
 * TYPE DECLARATIONS
 *****************************************************/

/** container for a entity component */
typedef struct COMPONENT COMPONENT_T;

/*****************************************************
 * TYPE IMPLEMENTATIONS
 *****************************************************/

typedef struct COMPONENT {
	/** system component belongs to. */
	SYSTEM_T* system;
	/** the entity the payload belong to. */
	ENTITY_T* entity;
	/** payload attached to component. */
	void* payload;
	/** status of the component. */
	STATUS_T status;
} COMPONENT_T;

/*****************************************************
 * FUNCTION DECLARATIONS
 *****************************************************/

/*****************************************************
 * FUNCTION IMPLEMENTATIONS
 *****************************************************/

/**
 * create a component.
 * @param payload data to attach to component.
 * @param system_id system the component belongs to.
 * @returns returns a generated component.
 */
COMPONENT_T* component__create(void* payload, SYSTEM_T* system);

#endif