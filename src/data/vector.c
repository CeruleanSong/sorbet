#include "vector.h"

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

/*****************************************************
 * FUNCTION IMPLEMENTATIONS
 *****************************************************/

VECTOR_T* vector__create(size_t inital_size)
{
	VECTOR_T* vector = malloc(sizeof(VECTOR_T));
	if(!vector)
	{
		return NULL;
	}

	vector->data = malloc(inital_size * sizeof(void));
	vector->used = 0;
	vector->size = inital_size;

	return vector;
} // vector__create()

void vector__insert(VECTOR_T* vector, void* item)
{
	if (vector->used == vector->size)
	{
		vector->size *= 2;
		vector->data = realloc(vector->data, vector->size * sizeof(void));
	}

	vector->data[vector->used++] = item;
} // vector__insert()

void* vector__get(VECTOR_T* vector, size_t index)
{
	if((index >= 0) && (index < vector->size))
	{
		return vector->data[index];
	}
	
	return NULL;
} // vector__get()

void* vector__remove(VECTOR_T* vector, size_t index)
{
	if((index >= 0) && (index < vector->size))
	{
		void* tmp = vector->data[index];
		vector->data[index] = NULL;
		return tmp;
	}
	
	return NULL;
} // vector__remove()

void vector__free(VECTOR_T* vector)
{
	if(vector)
	{
		free(vector->data);
		vector->data = NULL;
		vector->used = vector->size = 0;
		free(vector);
	}
} // vector__free()