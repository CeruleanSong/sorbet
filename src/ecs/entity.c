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

ENTITY_T* entity__create(void* payload, void (*tick), void (*render))
{
	ENTITY_T* entity = malloc(sizeof(ENTITY_T));
	if(!entity) { return NULL; }

	entity->entity_id = NULL;
	entity->component_list = vector__create(1);
	entity->payload = payload;
	entity->status = UNLINKED;
	entity->tick = tick;
	entity->render = render;

	return entity;
} // entity__create()

bool entity__attach_component(ENTITY_T* entity, COMPONENT_T* component)
{
	component->entity = entity;
	vector__insert(entity->component_list, component);
} // entity__register_component()