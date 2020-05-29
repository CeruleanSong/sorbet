#ifndef ECS_SYSTEM_H
#define ECS_SYSTEM_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../data.h"
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

SYSTEM_T* system__create(void (*func));

bool system__link_component(SYSTEM_T* s, ENTITY_T* e);

COMPONENT_T* system__unlink_component(SYSTEM_T* s,
	ECS__COLLECTION_SIZE_T component_id);

/*****************************************************
 * FUNCTION IMPLEMENTATIONS
 *****************************************************/

#endif