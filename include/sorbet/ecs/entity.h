#ifndef ECS_ENTITIY_H
#define ECS_ENTITIY_H

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

ENTITY_T* entity__create(ECS__COMPONENT_BIT_T components, void* payload);

/*****************************************************
 * FUNCTION IMPLEMENTATIONS
 *****************************************************/

#endif