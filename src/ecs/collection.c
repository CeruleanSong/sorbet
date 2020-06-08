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

COLLECTION_T* collection__create()
{
	COLLECTION_T* colection = malloc((sizeof(COLLECTION_T)));
	if(!colection) { return NULL; }

	colection->system_count = 0;
	colection->system_list = vector__create(1);

	colection->entity_count = 0;
	colection->entity_list = vector__create(1);

	colection->id_count = 0;
	colection->id_pool = queue_create(ECS__ENTITIES_MAX);

	return colection;
} // collection__create()

bool collection__attach_system(COLLECTION_T* collection, SYSTEM_T* system)
{
	vector__insert(collection->system_list, system);
	system->status = DISABLED;

	collection->system_count++;
} // collection__register_system()

bool collection__attach_entity(COLLECTION_T* collection, ENTITY_T* entity)
{
	ID_T* entity_id = NULL;

	if(queue_empty(collection->id_pool)
		&& (collection->id_count < ECS__ENTITIES_MAX))
	{
		ID_T* new_id = malloc(sizeof(ID_T));
		*new_id = collection->id_count++;

		queue_push(collection->id_pool, new_id);
	}

	entity_id = queue_pop(collection->id_pool);

	if(entity_id)
	{
		vector__insert(collection->entity_list, entity);
		entity->status = DISABLED;
		entity->entity_id = entity_id;
		collection->entity_count++;

		return true;
	}

	return false;
} // collection__register_entity()

void collection__link(COLLECTION_T* collection)
{
	size_t num_entities = collection->entity_list->size;

	for(size_t i = 0; i<num_entities; i++)
	{
		ENTITY_T* entity = collection->entity_list->data[i];
		VECTOR_T* component_list = entity->component_list;

		for(int j = 0; j<component_list->size; j++)
		{
			if(component_list->data[j])
			{
				COMPONENT_T* component = component_list->data[j];
				system__attach_component(component->system, component);
			}
		}
	}
} // collection__link_components()

void collection__flush(COLLECTION_T* collection)
{
	SYSTEM_T* system = NULL;
	for(size_t i = 0; i<collection->system_list->size; i++)
	{
		system = collection->system_list->data[i];
		if(system)
		{
			system__flush(system);
		}
	}
} // collection__flush()

void collection__tick(SORBET_T* sorbet, COLLECTION_T* collection)
{
	SYSTEM_T* system = NULL;
	LLIST_NODE_T* component = NULL;

	for(size_t i = 0; i<collection->system_count; i++)
	{
		system = collection->system_list->data[i];
		component = system->component_list->head;

		while(component && system->tick)
		{
			system->tick(sorbet, system, component->data);
			component = component->next;
		}
	}
} // collection__tick()