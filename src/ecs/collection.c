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
	COLLECTION_T *c = malloc(sizeof(COLLECTION_T));
	if(!c) {
		// TODO: logging
		return NULL;
	}

	c->system_count = 0;
	c->entity_count = 0;

	c->pool = queue_create(ECS__COLLECTION_MAX);

	for(ECS__COLLECTION_SIZE_T i = 0; i < ECS__COLLECTION_MAX; i++) {
		c->systems[i] = NULL;
	}

	for(ECS__COLLECTION_SIZE_T i = 0; i < ECS__COLLECTION_MAX; i++) {
		c->entities[i] = NULL;
	}

	// TODO: logging
	return c;
} // COLLECTION_T* collection__create()

bool collection__link_system(COLLECTION_T* c, SYSTEM_T* s,
	ECS__COLLECTION_SIZE_T id_code)
{
	OBJECT_ID_T* id = malloc(sizeof(OBJECT_ID_T));
	if(!id) {
		// TODO: logging
		return false;
	}

	s->system_id = id;
	id->collection = c;
	id->code = id_code;

	c->systems[c->system_count++] = s;

	return true;
} // collection_link_system()

bool collection__link_entity(COLLECTION_T* c, ENTITY_T* e)
{
	if(!(e->status & ENABLED)) {
		if(c->pool->size == 0) {
			// TODO: logging
			if(c->entity_count == (ECS__COLLECTION_MAX-1)) { return false; }

			OBJECT_ID_T* object_id = malloc(sizeof(OBJECT_ID_T));
			if(!object_id) {
				// TODO: logging
				return false;
			}

			object_id->collection = c;
			object_id->code = c->entity_count;

			queue_push(c->pool, object_id);
			c->entity_count++;
		}

		OBJECT_ID_T* object_id = queue_pop(c->pool);

		for(ECS__COLLECTION_SIZE_T i = 0; i<c->system_count; i++) {
			if(e->components & c->systems[i]->system_id->code) {
				c->systems[i]->table[object_id->code] = e;
			}
		}

		c->entities[object_id->code] = e;
		e->entity_id = object_id;
		e->status = ENABLED;

		// TODO: logging
		return true;
	} else {
		return false;
	}
} // bool collection__link_entity()

ENTITY_T* collection__unlink_entity(COLLECTION_T* c,
	ECS__COLLECTION_SIZE_T entity_id)
{
	if(c->entity_count > 0 && c->entities[entity_id]) {
		// TODO: logging
		ENTITY_T* entity = c->entities[entity_id];
		OBJECT_ID_T* id = c->entities[entity_id]->entity_id;

		entity->status = EXPUNGE;
		entity->entity_id = NULL;

		queue_push(c->pool, id);

		return entity;
	} else {
		return NULL;
	}
} // ENTITY_T* collection__unlink_entity()
