
#include "hashmap.h"

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

HASHMAP_T* hashmap__create()
{
	HASHMAP_T* h = malloc(sizeof(HASHMAP_T));
	if(!h) {
		// TODO: logging
		return NULL;
	}

	h->data = vector__create(50);
	h->size = 50;

	return h;
}

size_t hashmap__code(HASHMAP_T* h, size_t key)
{
   return key % h->size;
}

HASHMAP_T* hashmap__search(HASHMAP_T* h, size_t key)
{
	int index = hashmap__code(h,key);  

	while(h->data->array[index] != NULL) {

		if(((HASHMAP_ITEM_T*)h->data->array[index])->key == key)
			return h->data->array[index]; 
			
		++index;
		index %= h->size;
	}        

	return NULL; 
}

void hashmap__insert(HASHMAP_T* h, size_t key, void* data)
{
	HASHMAP_ITEM_T* item = malloc(sizeof(HASHMAP_ITEM_T));
	item->data = data;  
	item->key = key;

	size_t index = hashmap__code(h, key);

	while(h->data->array[index] != NULL
		&& ((HASHMAP_ITEM_T*)h->data->array[index])->key != -1) {
			
		++index;
			
		//wrap around the table
		index %= h->size;
	}
		
	h->data->array[index] = item;
}

HASHMAP_ITEM_T* hashmap__remove(HASHMAP_T* h, size_t key)
{
	int index = hashmap__code(h, key);

	while(h->data->array[index] != NULL) {
		
		if(((HASHMAP_ITEM_T*)h->data->array[index])->key == key) {
			HASHMAP_ITEM_T* temp = h->data->array[index]; 
				
			//assign a dummy item at deleted position
			h->data->array[index] = NULL; 
			return temp;
		}
			
		++index;
			
		index %= h->size;
	}      
		
	return NULL;
}

void hashmap__free(HASHMAP_T* h)
{
	vector__free(h->data);
	free(h);
}