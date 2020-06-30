#ifndef DATA_MAP_H
#define DATA_MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*****************************************************
 * ENUMERATIONS
 *****************************************************/

/*****************************************************
 * TYPE DECLARATIONS
 *****************************************************/

/** container for a linked list. */
typedef struct LLIST LLIST_T;

/*****************************************************
 * TYPE IMPLEMENTATIONS
 *****************************************************/

typedef struct MAP {
	MAP_NODE_T *head;
} MAP_T;

typedef struct MAP_NODE {
	void *data;
	MAP_NODE_T *right;
	MAP_NODE_T *left;
} MAP_NODE_T;


/*****************************************************
 * FUNCTION DECLARATIONS
 *****************************************************/

/** 
 * create an empty linked list.
 * @returns an empty linked list.
 **/
MAP_T* map__create();

/*****************************************************
 * FUNCTION IMPLEMENTATIONS
 *****************************************************/

#endif