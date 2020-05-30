#include "llist.h"

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

LLIST_T* llist_create()
{
	LLIST_T* llist = malloc(sizeof(LLIST_T));
	if(!llist) { return NULL; }

	llist->head = NULL;
	llist->tail = NULL;
	llist->size = 0;
} // llist_create

void llist_push_head(LLIST_T* llist, size_t key, void* item)
{
	LLIST_NODE_T* node = malloc(sizeof(LLIST_NODE_T));
	if(!node) { return; }

	node->back = llist->tail;
	node->next = NULL;

	node->key = key;
	node->data = item;

	if(llist->tail)
	{
		llist->tail->next = node;
		llist->tail = node;
	}
	else
	{
		llist->tail = node;
		llist->head = node;
	}
	++llist->size;
} // llist_push_head()

void llist_push_tail(LLIST_T* llist, size_t key, void* item)
{
	LLIST_NODE_T* node = malloc(sizeof(LLIST_NODE_T));
	if(!node) { return; }

	node->next = llist->head;
	node->back = NULL;
	
	node->key = key;
	node->data = item;

	if(llist->head)
	{
		llist->head->back = node;
		llist->head = node;
	}
	else
	{
		llist->tail = node;
		llist->head = node;
	}
	++llist->size;
} // llist_push_tail()

LLIST_NODE_T* llist_pop(LLIST_T* llist, size_t key)
{
	LLIST_NODE_T* node = llist->head;

	while(node && !(node->key == key))
	{
		node = node->next;
	}

	if(node)
	{
		if(node->back)
		{
			node->back->next = node->next;
		}
		else
		{
			llist->head = node->next;
		}

		if(node->next)
		{
			node->next->back = node->back;
		}
		else
		{
			llist->tail = node->back;
		}

		node->back = NULL;
		node->next = NULL;
		--llist->size;
	}
	
	return node;
} // llist_pop()

LLIST_NODE_T* llist_get(LLIST_T* llist, size_t key)
{
	LLIST_NODE_T* node = llist->head;

	while(node && !(node->key == key))
	{
		node = node->next;
	}

	return node;
} // llist_get()

LLIST_NODE_T* llist_peek_head(LLIST_T* llist)
{
	return llist->head;
} // llist_peek_head()

LLIST_NODE_T* llist_peek_tail(LLIST_T* llist)
{
	return llist->tail;
} // llist_peek_tail()

LLIST_NODE_T* llist_cycle(LLIST_T* llist)
{
	LLIST_NODE_T* node = llist_peek_head(llist);
	if(node)
	{
		llist_pop(llist, node->key);
		llist_push_tail(llist, node->key, node->data);

		free(node);

		return llist_peek_tail(llist);
	}
	
	return NULL;
} // llist_cycle()

void llist_free(LLIST_T* llist)
{
	if(llist)
	{
		llist_node_free(llist->head);
		free(llist);
		llist = NULL;
	}
} // llist_free()

void llist_node_free(LLIST_NODE_T* node)
{
	if(node->next) { llist_node_free(node->next); }
	free(node);
	node = NULL;
} // llist_node_free()