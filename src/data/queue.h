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

/** container for a circular queue. */
typedef struct QUEUE QUEUE_T;

/*****************************************************
 * TYPE IMPLEMENTATIONS
 *****************************************************/

typedef struct QUEUE {
    size_t front; // index of front item in queue.
	size_t rear; // index of rear item in queue.
	size_t used; // filled up slots in queue.
	size_t size; // maximum capacity of queue.
	void** data; // queue array.
} QUEUE_T;

/*****************************************************
 * FUNCTION DECLARATIONS
 *****************************************************/

/** 
 * create an empty queue.
 * @param size length of queue.
 * @returns an empty queue.
 **/
QUEUE_T* queue_create(size_t size);

/**
 * check whether a queue is empty.
 * @param queue queue to check.
 * @returns true if empty false if not.
 **/
bool queue_empty(QUEUE_T* queue);

/**
 * check whether a queue is full.
 * @param queue queue to check.
 * @returns true if full false if not.
 **/
bool queue_full(QUEUE_T* queue);

/**
 * insert an item into a queue.
 * @param queue queue to modify.
 * @param item item to insert into queue.
 * @returns true if successful false if not.
 **/
bool queue_push(QUEUE_T* queue, void* item);

/**
 * remove an item from a queue.
 * @param queue queue to modify.
 * @returns the item removed from the queue (NULL if empty).
 **/
void* queue_pop(QUEUE_T* queue);

/**
 * cycle an item into the back of a queue.
 * @param queue queue to modify.
 * @returns the item cycled to back of queue (NULL if empty).
 **/
void* queue_cycle(QUEUE_T* queue);

/*****************************************************
 * FUNCTION IMPLEMENTATIONS
 *****************************************************/

#endif