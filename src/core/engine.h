#ifndef CORE_GAME_H
#define CORE_GAME_H

#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "../types.h"
#include "../ecs/collection.h"

/*****************************************************
 * ENUMERATIONS
 *****************************************************/

/*****************************************************
 * TYPE DECLARATIONS
 *****************************************************/

/** core sorbet object */
typedef struct SORBET SORBET_T;
/** options for initializing sorbet object. */
typedef struct SORBET_OPTIONS SORBET_OPTIONS_T;
/** collection of time steps */
typedef struct SORBET_TIME SORBET_TIME_T;

/*****************************************************
 * TYPE IMPLEMENTATIONS
 *****************************************************/

typedef struct SORBET {
	/** options for context */
	SORBET_OPTIONS_T* options;
	/** refrence to window */
	GLFWwindow* window;
	/** record of time */
	SORBET_TIME_T* time;
	/** ecs collection */
	COLLECTION_T* collection;
	/** exit flag for context */
	bool exit;
} SORBET_T;

typedef struct SORBET_TIME {
	/** current time step */
	SORBET_LENGTH_T current;
	/** last time step */
	SORBET_LENGTH_T last;
	/** time betweent steps */
	SORBET_LENGTH_T delta;
} SORBET_TIME_T;

typedef struct SORBET_OPTIONS {
	/** window title */
	char* title;
	/** window dimensions */
	short width, height, x, y;
	/** target window framerate */
	short framerate;
	/** development env flags */
	bool debug;
	/** ecs collection */
	COLLECTION_T* collection;
} SORBET_OPTIONS_T;

/*****************************************************
 * FUNCTION DECLARATIONS
 *****************************************************/

/**
 * generate a blank sorbet context.
 * @returns an empty sorbet object.
 **/
SORBET_T* sorbet__create();

/**
 * destroy a sorbet context.
 * @param sorbet the sorbet context to destory.
 **/
void sorbet__destory(SORBET_T* sorbet);

/**
 * initialize a sorbet context.
 * @param sorbet sorbet context to be initialized.
 * @param options options to apply to sorbet context.
 * @returns true if successful else false.
 **/
bool sorbet__init(SORBET_T* sorbet, SORBET_OPTIONS_T* options);

/**
 * centere a window onto the screen.
 * @param sorbet sorbet context to be centered.
 * @returns the monitor that teh context was centered on.
 **/
GLFWmonitor* sorbet__center_window(SORBET_T* sorbet);

/**
 * attempt to gracefully uninitialize a sorbet context.
 * @param sorbet sorbet context to be uninitialize.
 * @returns true if successful else false.
 **/
bool sorbet__exit(SORBET_T* sorbet);

/**
 * compute a tick in a sorbet context.
 * @param sorbet sorbet context to compute.
 */
void sorbet__tick(SORBET_T* sorbet);

/**
 * draw the current tick in a sorbet context.
 * @param sorbet sorbet context to draw.
 */
void sorbet__draw(SORBET_T* sorbet);

/*****************************************************
 * FUNCTION IMPLEMENTATIONS
 *****************************************************/

#endif