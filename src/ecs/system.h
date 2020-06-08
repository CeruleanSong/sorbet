#ifndef ECS_SYSTEM_H
#define ECS_SYSTEM_H

#include <stdbool.h>

#include "../types.h"
#include "../core/engine.h"
#include "../set/llist.h"

#include "component.h"

typedef struct SORBET SORBET_T;
typedef struct COMPONENT COMPONENT_T;

/*****************************************************
 * ENUMERATIONS
 *****************************************************/

/*****************************************************
 * TYPE DECLARATIONS
 *****************************************************/

/** container for a system */
typedef struct SYSTEM SYSTEM_T;

/*****************************************************
 * TYPE IMPLEMENTATIONS
 *****************************************************/

typedef struct SYSTEM {
	/** id of the system. */
	ID_T system_id;
	/** list of attached components */
	LLIST_T* component_list;
	/** status of the system. */
	STATUS_T status;
	/** update function */
	void (*tick)(SORBET_T* sorbet, SYSTEM_T* system, COMPONENT_T* component);
} SYSTEM_T;

/*****************************************************
 * FUNCTION DECLARATIONS
 *****************************************************/

/*****************************************************
 * FUNCTION IMPLEMENTATIONS
 *****************************************************/

/**
 * create a blank system container.
 * @param func the system logic function.
 * @param system_id identifier code of the system.
 * @returns a generated system.
 */
SYSTEM_T* system__create(void (*func), ID_T system_id);

/**
 * register an component to a system.
 * @param system system to modify.
 * @param component component to attach.
 * @returns true if success false if not.
 */
bool system__attach_component(SYSTEM_T* system, COMPONENT_T* component);

/**
 * expunge a collection.
 * @param system system to modify.
 */
void system__flush(SYSTEM_T* system);

#endif