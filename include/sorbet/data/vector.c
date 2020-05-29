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
	VECTOR_T* v = malloc(sizeof(VECTOR_T));
	if(!v) {
		// TODO: logging
		return NULL;
	}

	v->array = malloc(inital_size * sizeof(void));
	v->used = 0;
	v->size = inital_size;

	return v;
} // vector__create()

void vector__insert(VECTOR_T* v, void* item)
{
	if (v->used == v->size)
	{
		v->size *= 2;
		v->array = realloc(v->array, v->size * sizeof(void));
	}

	v->array[v->used++] = item;
} // vector__insert()

void vector__remove(VECTOR_T* v, size_t index)
{
	if(v->size > index)
	{
		if(v->array[index]) { free(v->array[index]); }
		v->array[index] = NULL;

		vector__shrink(v);
	}
} // vector__remove()

void vector__shrink(VECTOR_T* v)
{
	size_t valid = 0;
	size_t empty = 0;
	for(size_t i=0; (i<v->size) && (valid<v->used); i++)
	{
		if(v->array[i]) {
			v->array[i-empty] = v->array[i];
			valid++;
		} else {
			empty++;
		}
	}
} // vector__shrink()

void vector__free(VECTOR_T* v)
{
	free(v->array);
	v->array = NULL;
	v->used = v->size = 0;

	free(v);
} // vector__free()