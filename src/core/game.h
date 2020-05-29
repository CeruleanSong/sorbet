#ifndef CORE_GAME_H
#define CORE_GAME_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../ecs/collection.h"

/*****************************************************
 * ENUMERATIONS
 *****************************************************/

/*****************************************************
 * TYPE DECLARATIONS
 *****************************************************/

typedef struct SORBET SORBET_T;

typedef struct s_options s_options_t;

/*****************************************************
 * TYPE IMPLEMENTATIONS
 *****************************************************/

typedef struct SORBET {
	bool quit;
	s_options_t* options;
	SDL_Window* window;
	SDL_Surface* surface;
	SDL_Renderer* renderer;
} SORBET_T;

typedef struct s_options {
	char* title;
	short width;
	short height;
	short fps;
	uint32_t flags;
	COLLECTION_T* collection;
} s_options_t;

/*****************************************************
 * FUNCTION DECLARATIONS
 *****************************************************/

/** create a sorbet object */
SORBET_T* sorbet__create(void);
/** init SDL2 systems */
void sorbet__init(SORBET_T* sorbet, s_options_t* options);
/** start game loop */
void sorbet__run(SORBET_T* sorbet);
/** start game loop */
void sorbet__exit(SORBET_T* sorbet);

/*****************************************************
 * FUNCTION IMPLEMENTATIONS
 *****************************************************/

/** function implemented by developer, init game state */
extern void (*sorbet__main)(void);

#endif