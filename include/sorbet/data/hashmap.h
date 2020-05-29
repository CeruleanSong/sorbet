
#ifndef DATA_HASHMAP_H
#define DATA_HASHMAP_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "vector.h"

/*****************************************************
 * ENUMERATIONS
 *****************************************************/

/*****************************************************
 * TYPE DECLARATIONS
 *****************************************************/

typedef struct HASHMAP_ITEM HASHMAP_ITEM_T;

typedef struct HASHMAP HASHMAP_T;

/*****************************************************
 * TYPE IMPLEMENTATIONS
 *****************************************************/

typedef struct HASHMAP_ITEM {
	void* data;
	size_t key;
} HASHMAP_ITEM_T;

typedef struct HASHMAP {
	VECTOR_T* data;
	size_t size;
} HASHMAP_T;

/*****************************************************
 * FUNCTION DECLARATIONS
 *****************************************************/

HASHMAP_T* hashmap__create();
size_t hashmap__code(HASHMAP_T* h, size_t key);
HASHMAP_T* hashmap__search(HASHMAP_T* h, size_t key);
void hashmap__insert(HASHMAP_T* h, size_t key, void* item);
HASHMAP_ITEM_T* hashmap__remove(HASHMAP_T* h, size_t key);
void hashmap__free(HASHMAP_T* h);

/*****************************************************
 * FUNCTION IMPLEMENTATIONS
 *****************************************************/

#endif