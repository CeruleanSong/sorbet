#ifndef DATA_LLIST_H
#define DATA_LLIST_H

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

/** container for a linked list. */
typedef struct LLIST LLIST_T;

/** container for a linked list node. */
typedef struct LLIST_NODE LLIST_NODE_T;

/*****************************************************
 * TYPE IMPLEMENTATIONS
 *****************************************************/

typedef struct LLIST {
    LLIST_NODE_T* head; // front item in linked listl.
	LLIST_NODE_T* tail; // rear item in linked listl.
	size_t size; // length of linked listl
} LLIST_T;

typedef struct LLIST_NODE {
    LLIST_NODE_T* next; // next item.
	LLIST_NODE_T* back; // previous item.
	size_t key; // key of node.
	void* data; // payload.
} LLIST_NODE_T;

/*****************************************************
 * FUNCTION DECLARATIONS
 *****************************************************/

/** 
 * create an empty linked list.
 * @returns an empty linked list.
 **/
LLIST_T* llist__create();

/**
 * insert an item into the front of a linked list.
 * @param llist linked list to modify.
 * @param item item to insert into linked list.
 **/
void llist__push_head(LLIST_T* llist, size_t key, void* item);

/**
 * insert an item into the back of a linked list.
 * @param llist linked list to modify.
 * @param item item to insert into linked list.
 **/
void llist__push_tail(LLIST_T* llist, size_t key, void* item);

/**
 * insert an node into the front of a linked list.
 * @param llist linked list to modify.
 * @param node node to insert into linked list.
 **/
void llist__push_node_head(LLIST_T* llist, LLIST_NODE_T* node);

/**
 * insert an node into the back of a linked list.
 * @param llist linked list to modify.
 * @param node node to insert into linked list.
 **/
void llist__push_node_tail(LLIST_T* llist, LLIST_NODE_T* node);

/**
 * remove an item from a linked list.
 * @param llist linked list to modify.
 * @param key the key of the item to remove.
 * @returns the item removed from the linked list (NULL if not found).
 **/
LLIST_NODE_T* llist__pop(LLIST_T* llist, size_t key);

/**
 * remove all items from a linked list.
 * @param llist linked list to modify.
 * @returns a pointer to the head node.
 **/
LLIST_NODE_T* llist__pop_all(LLIST_T* llist);

/**
 * get an item from a linked list.
 * @param llist linked list to modify.
 * @param key the key of the item to get.
 * @returns the item with the specified key (NULL if not found).
 **/
LLIST_NODE_T* llist__get(LLIST_T* llist, size_t key);

/**
 * get the head of a linked list.
 * @param llist linked list to view.
 * @returns the linked list head (NULL if not found).
 **/
LLIST_NODE_T* llist__peek_head(LLIST_T* llist);

/**
 * get the tail of a linked list.
 * @param llist linked list to view.
 * @returns the linked list tail (NULL if not found).
 **/
LLIST_NODE_T* llist__peek_tail(LLIST_T* llist);

/**
 * cycle an item into the back of a linked list.
 * @param llist linked list to modify.
 * @returns the item cycled to back of linked list (NULL if empty).
 **/
LLIST_NODE_T* llist__cycle(LLIST_T* llist);

/**
 * free a linked list from memory.
 * @param llist linked list to free;
 **/
void llist__free(LLIST_T* llist);

/**
 * free a linked list node from memory.
 * @param node node to free
 **/
void llist__node_free(LLIST_NODE_T* node);

/*****************************************************
 * FUNCTION IMPLEMENTATIONS
 *****************************************************/

#endif