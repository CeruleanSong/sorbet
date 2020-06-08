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
	system->component_list = llist__create();
	system->status = UNLINKED;
	system->tick = func;
} // system__create()

bool system__attach_component(SYSTEM_T* system, COMPONENT_T* component)
{
	component->status = ENABLED;
	llist__push_head(system->component_list, *component->entity->entity_id,
		component);
} // system__attach_component()

void system__flush(SYSTEM_T* system)
{
	LLIST_NODE_T* node = llist__peek_head(system->component_list);
	LLIST_NODE_T* next = node;
	
	while(next)
	{
		COMPONENT_T* component = (COMPONENT_T*) next->data;
		component->status = UNLINKED;

		next = node->next;
		llist__free_node(node);
	}

	system->component_list->head = NULL;
	system->component_list->tail = NULL;
	system->component_list->size = 0;
} // system__flush()