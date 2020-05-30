
#ifndef DATA_VECTOR_H
#define DATA_VECTOR_H

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

/** a dynamically resizing arary */
typedef struct VECTOR VECTOR_T;

/*****************************************************
 * TYPE IMPLEMENTATIONS
 *****************************************************/

typedef struct VECTOR {
	void** data; // vector array.
	size_t used; // used indexes of vector.
	size_t size; // total size of vector.
} VECTOR_T;

/*****************************************************
 * FUNCTION DECLARATIONS
 *****************************************************/

/**
 * create a vector (dynamic array).
 * @param initial_size initial size of vector.
 * @returns an empty vector of the specfied size.
 **/
VECTOR_T* vector__create(size_t initial_size);

/**
 * insert an item into a vector.
 * @param vector vector to modify.
 * @param item the item to insert.
 **/
void vector__insert(VECTOR_T* vector, void* item);

/**
 * retrieve a value from a vector.
 * @param vector the vetor to grab from.
 * @returns the specified item (null if index out of bounds).
 **/
void* vector__get(VECTOR_T* vector, size_t index);

/**
 * remove an item from a vector.
 * @param vector vector to modify.
 * @param index index of the item to remove.
 * @returns the removed item (null if index out of bounds).
 **/
void* vector__remove(VECTOR_T* vector, size_t index);

/**
 * free a vector from memory (if it exists).
 * @param vector the vector to free.
 **/
void vector__free(VECTOR_T* vector);

/*****************************************************
 * FUNCTION IMPLEMENTATIONS
 *****************************************************/

#endif