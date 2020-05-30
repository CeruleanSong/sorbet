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

SYSTEM_T* system__create(void (*func), ID_T system_id)
{
	SYSTEM_T* system = malloc(sizeof(SYSTEM_T));
	if(!system) { return NULL; }

	system->system_id = system_id;
	system->components = llist_create();
	system->status = UNLINKED;
	system->func = func;
} // system__create()

bool system__register_component(SYSTEM_T* system, COMPONENT_T* component)
{
	component->status = ENABLED;
	llist_push_head(system->components, *component->entity->entity_id,
		component);
} // system__register_component()

void system__flush(SYSTEM_T* system)
{
	LLIST_NODE_T* head = llist_pop_all(system->components);
	LLIST_NODE_T* node = head;
	while(head)
	{
		COMPONENT_T* component = (COMPONENT_T*) head->data;
		component->status = UNLINKED;

		head = head->next;
	}
} // system__flush()