#ifndef ECS_COMPONENT_H
#define ECS_COMPONENT_H

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

void component__create(COLLECTION_T* c);

void component__register_entity(ECS__COMPONENT_BIT_T b, ENTITY_T e);

/*****************************************************
 * FUNCTION IMPLEMENTATIONS
 *****************************************************/

#endif