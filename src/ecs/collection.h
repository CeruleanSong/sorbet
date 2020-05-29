#ifndef ECS_COLLECTION_H
#define ECS_COLLECTION_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../data.h"

// #ifndef ECS__COLLECTION_SIZE_T
// #define ECS__COLLECTION_SIZE_T unsigned long
// #endif

typedef unsigned long int ECS__COMPONENT_BIT_T;

typedef unsigned long int ECS__COLLECTION_SIZE_T;

#ifndef ECS__COLLECTION_MAX
#define ECS__COLLECTION_MAX ((ECS__COLLECTION_SIZE_T)1) << 24
#endif

/*****************************************************
 * ENUMERATIONS
 *****************************************************/

typedef enum ENTITY_STATUS {
	DISABLED,
	ENABLED,
	EXPUNGE,
	ENTITY_STATUS_MAX
} ENTITY_STATUS_T;

/*****************************************************
 * TYPE DECLARATIONS
 *****************************************************/

typedef struct COLLECTION COLLECTION_T;

typedef struct ENTITY ENTITY_T;

typedef struct OBJECT_ID OBJECT_ID_T;

typedef ENTITY_T* ENTITY_TABLE_T;

typedef QUEUE_T* ENTITY_POOL_T;

typedef struct SYSTEM SYSTEM_T;

typedef SYSTEM_T* SYSTEM_LIST_T;

typedef ENTITY_T COMPONENT_T;

typedef ENTITY_T* COMPONENT_TABLE_T;

/*****************************************************
 * TYPE IMPLEMENTATIONS
 *****************************************************/

typedef struct COLLECTION {
	ECS__COLLECTION_SIZE_T system_count;
	SYSTEM_LIST_T systems[ECS__COLLECTION_MAX];
	ECS__COLLECTION_SIZE_T entity_count;
	ENTITY_TABLE_T entities[ECS__COLLECTION_MAX];
	
	ENTITY_POOL_T pool;
} COLLECTION_T;

typedef struct ENTITY {
	OBJECT_ID_T* entity_id;
	ECS__COMPONENT_BIT_T components;
	ENTITY_STATUS_T status;
	void* payoad;
} ENTITY_T;

typedef struct OBJECT_ID {
	COLLECTION_T* collection;
	ECS__COLLECTION_SIZE_T code;
} OBJECT_ID_T;

typedef struct SYSTEM {
	OBJECT_ID_T* system_id;
	COMPONENT_TABLE_T table[ECS__COLLECTION_MAX];
	void (*func)(SDL_Event* event, ENTITY_T* e, COMPONENT_TABLE_T table[]);
} SYSTEM_T;

/*****************************************************
 * FUNCTION DECLARATIONS
 *****************************************************/

COLLECTION_T* collection__create();

bool collection__link_system(COLLECTION_T* c, SYSTEM_T* s,
	ECS__COLLECTION_SIZE_T id_code);

bool collection__link_entity(COLLECTION_T* c, ENTITY_T* e);

ENTITY_T* collection__unlink_entity(COLLECTION_T* c,
	ECS__COLLECTION_SIZE_T entity_id);
	
/*****************************************************
 * FUNCTION IMPLEMENTATIONS
 *****************************************************/

#endif