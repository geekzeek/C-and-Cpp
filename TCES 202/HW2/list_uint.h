/*
 * list_int.h
 *
 *  Created on: Jan 28, 2015
 *      Author: mmuppa
 */

#ifndef LIST_UINT_H_
#define LIST_UINT_H_

typedef unsigned int UINT;
// Declare a structure for the list
struct list_node
{
	UINT value;
	struct list_node *next;
};

typedef struct list_node anode;

struct list
{
	struct list_node *head;	// List head pointer
};

typedef struct list alist;

// Prototypes
void insert_node_at_index(alist *, UINT, UINT); //Insert a new node with the value at the given index
UINT size(alist *); //Returns the number of nodes in the list
UINT delete_node_at_index(alist *, UINT); //Delete the node at the given index and return the value.
UINT sum_nodes(alist *); //Returns the sum of the values in the nodes
void delete_node(alist *, UINT); // Delete the node with the given value
void insert_node(alist *, UINT); // Insert the new node in the right position
void append_node(alist *, UINT); // Add a new node
void display_list(alist *); // Display the list
void free_list(alist *); // free the memory

#endif /* LIST_UINT_H_ */
