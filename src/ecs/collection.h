#ifndef ECS_COLLECTION_H
#define ECS_COLLECTION_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../types.h"
#include "../set/queue.h"
#include "../set/vector.h"

#include "system.h"
#include "entity.h"

typedef struct ENTITY ENTITY_T;
typedef struct SYSTEM SYSTEM_T;

/*****************************************************
 * ENUMERATIONS
 *****************************************************/

/*****************************************************
 * TYPE DECLARATIONS
 *****************************************************/

/** container for a collection */
typedef struct COLLECTION COLLECTION_T;

/*****************************************************
 * TYPE IMPLEMENTATIONS
 *****************************************************/

typedef struct COLLECTION {
	/** # of systems in collection */
	size_t system_count;
	/** list of all systems */
	VECTOR_T* system_list;
	/** # of entities in collection */
	size_t entity_count;
	/** list of all entities */
	VECTOR_T* entity_list;
	/** # of id's created */
	size_t id_count;
	/** queue of available id's */
	QUEUE_T* id_pool;
} COLLECTION_T;

/*****************************************************
 * FUNCTION DECLARATIONS
 *****************************************************/

/**
 * create an empty collection.
 * @returns a blank collection.
 */
COLLECTION_T* collection__create();

/**
 * register an system to a collection.
 * @param collection collection to add to.
 * @param system system to link.
 * @returns true if successful, else false.
 */
bool collection__attach_system(COLLECTION_T* collection, SYSTEM_T* system);

/**
 * register an entity to a collection.
 * @param collection collection to add to.
 * @param entity entity to link.
 * @returns true if successful, else false.
 */
bool collection__attach_entity(COLLECTION_T* collection, ENTITY_T* entity);

/**
 * insert every component into their corresponding system.
 * @param collection the collection to modify.
 */
void collection__link(COLLECTION_T* collection);

/**
 * expunge a collection.
 * @param collection collection to modify.
 */
void collection__flush(COLLECTION_T* collection);

/**
 * process a tick on every single system.
 * @param sorbet sorbet context to bind to.
 * @param collection the collection to process.
 */
void collection__tick(SORBET_T* sorbet, COLLECTION_T* collection);

/*****************************************************
 * FUNCTION IMPLEMENTATIONS
 *****************************************************/

#endif