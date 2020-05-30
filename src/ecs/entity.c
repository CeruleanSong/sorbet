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

ENTITY_T* entity__create(void* payload)
{
	ENTITY_T* entity = malloc(sizeof(ENTITY_T));
	if(!entity) { return NULL; }

	entity->entity_id = 0;
	entity->components = vector__create(1);
	entity->payload = payload;
	entity->status = UNLINKED;

	return entity;
} // entity__create()

void entity__register_component(ENTITY_T* entity, COMPONENT_T* component)
{
	component->entity = entity;
	vector__insert(entity->components, component);
} // entity__register_component()