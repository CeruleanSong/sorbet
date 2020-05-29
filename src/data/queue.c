#include "queue.h"

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

QUEUE_T* queue_create(size_t size)
{
	QUEUE_T* q = malloc(sizeof(QUEUE_T));
	if(!q) {
		// TODO: logging
		return NULL;
	}

	q->data = malloc(size);
	if(!q->data) {
		// TODO: logging
		return NULL;
	}
	
	q->capacity = size;
	q->front = q->size = 0;
    q->rear = size - 1;
} // queue_create()



bool queue_empty(QUEUE_T* q)
{
	if(q->size == 0) {
		return true;
	} else {
		return false;
	}
} // queue_empty()

bool queue_full(QUEUE_T* q)
{
	if(q->size == q->capacity) {
		return true;
	} else {
		return false;
	}
} // queue_full()

bool queue_push(QUEUE_T* q, void* item)
{
	if (queue_full(q) == true) {
		return false;
	} else {
		q->rear = (q->rear + 1) % q->capacity; 
		q->data[q->rear] = item; 
		q->size = q->size + 1; 
	}
	return true;
} // queue_push()

QUEUE_ITEM_T queue_pop(QUEUE_T* q)
{
	QUEUE_ITEM_T *pop_item = NULL;

    if (queue_empty(q) == true) 
        return pop_item;

    pop_item = q->data[q->front]; 
    q->front = (q->front + 1) % q->capacity; 
    q->size = q->size - 1; 

    return pop_item;
} // () queue_pop()