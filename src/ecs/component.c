#include "component.h"

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

COMPONENT_T* component__create(void* payload, SYSTEM_T* system)
{
	COMPONENT_T* component = malloc(sizeof(COMPONENT_T));
	if(!component) { return NULL; }

	component->system = system;
	component->entity = NULL;
	component->payload = payload;
	component->status = UNLINKED;

	return component;
} // component__create()