
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

typedef struct VECTOR VECTOR_T;

/*****************************************************
 * TYPE IMPLEMENTATIONS
 *****************************************************/

typedef struct VECTOR {
	void** array;
	size_t used;
	size_t size;
} VECTOR_T;

/*****************************************************
 * FUNCTION DECLARATIONS
 *****************************************************/

VECTOR_T* vector__create(size_t inital_size);

void vector__insert(VECTOR_T* v, void* item);
void vector__remove(VECTOR_T* v, size_t index);
void vector__shrink(VECTOR_T* v);
void vector__free(VECTOR_T* v);

/*****************************************************
 * FUNCTION IMPLEMENTATIONS
 *****************************************************/

#endif