#ifndef ECS_ENTITIY_H
#define ECS_ENTITIY_H

#include "../types.h"
#include "../core/engine.h"
#include "../set/vector.h"

#include "component.h"

typedef struct SORBET SORBET_T;
typedef struct COMPONENT COMPONENT_T;

/*****************************************************
 * ENUMERATIONS
 *****************************************************/

/*****************************************************
 * TYPE DECLARATIONS
 *****************************************************/

/** container for a entity */
typedef struct ENTITY ENTITY_T;

/*****************************************************
 * TYPE IMPLEMENTATIONS
 *****************************************************/

typedef struct ENTITY {
	/** id of the entity. */
	ID_T* entity_id;
	/** list of attached components */
	VECTOR_T* component_list;
	/** payload attached to entity. */
	void* payload;
	/** status of the entity. */
	STATUS_T status;
	/** update function */
	void (*tick)(SORBET_T* sorbet, ENTITY_T* entity);
	/** render function */
	void (*render)(SORBET_T* sorbet, ENTITY_T* entity);
} ENTITY_T;

/*****************************************************
 * FUNCTION DECLARATIONS
 *****************************************************/

/*****************************************************
 * FUNCTION IMPLEMENTATIONS
 *****************************************************/

/**
 * create an empty entity with a specified payload.
 * @param payload payload to attach to entity.
 * @param update update function.
 * @param tick tick function.
 */
ENTITY_T* entity__create(void* payload, void (*update), void (*tick));

/**
 * attach a component to an entity.
 * @param entity entity to modify.
 * @param component component to attach to entity.
 * @returns true if success false if not.
 */
bool entity__attach_component(ENTITY_T* entity, COMPONENT_T* component);

#endif