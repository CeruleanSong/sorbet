
#ifndef DATA_QUEUE_H
#define DATA_QUEUE_H

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

typedef struct QUEUE QUEUE_T;
typedef void* QUEUE_ITEM_T;

/*****************************************************
 * TYPE IMPLEMENTATIONS
 *****************************************************/

typedef struct QUEUE {
    size_t front, rear, size; 
	size_t capacity;
	void** data;
} QUEUE_T;

/*****************************************************
 * FUNCTION DECLARATIONS
 *****************************************************/

QUEUE_T* queue_create(size_t size);

bool queue_empty(QUEUE_T* q);
bool queue_full(QUEUE_T* q);
bool queue_push(QUEUE_T* q, void* item);
QUEUE_ITEM_T queue_pop(QUEUE_T* q);

/*****************************************************
 * FUNCTION IMPLEMENTATIONS
 *****************************************************/

#endif