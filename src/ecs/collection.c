#include "collection.h"

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

bool collection__register_system(COLLECTION_T* collection, SYSTEM_T* system)
{
	vector__insert(collection->system_list, system);
	system->status = DISABLED;

	collection->system_count++;
} // collection__register_system()

bool collection__register_entity(COLLECTION_T* collection, ENTITY_T* entity)
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

void collection__link_components(COLLECTION_T* collection)
{
	size_t size = collection->entity_list->size;
	size_t used = collection->entity_list->used;

	ENTITY_T* entity = NULL;
	COMPONENT_T* component = NULL;
	SYSTEM_T* system = NULL;

	for(size_t i = 0; i<size; i++)
	{
		entity = collection->entity_list->data[i];
		for(size_t j = 0; j<entity->components->size && entity; j++)
		{
			component = entity->components->data[j];
			for(size_t k = 0; k<collection->system_list->size && component; k++)
			{
				system = collection->system_list->data[k];
				if(system)
				{
					llist__push_head(system->components,
						*component->entity->entity_id, component);
				}
			}
		}
	}
} // collection__link_components()

void collection__flush_components(COLLECTION_T* collection)
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
} // collection__flush_componentsI()


void collection__tick(SORBET_T* sorbet, COLLECTION_T* collection,
	SDL_Event* event, SORBET_LENGTH_T delta)
{
	SYSTEM_T* system = NULL;
	LLIST_NODE_T* node = NULL;
	
	for(size_t i = 0; i<collection->system_count; i++)
	{
		system = collection->system_list->data[i];
		node = system->components->head;

		while(node)
		{
			if(node) {
				system->func(sorbet, system->components, event,
					node->data, delta);
				node = node->next;
			}
		}
	}
} // collection__tick()