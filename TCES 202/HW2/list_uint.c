/*
 * list_UINT.c
 *
 *  Created on: Jan 28, 2015
 *      Author: mmuppa
 */

#include <stdlib.h>
#include <stdio.h>
#include "list_uint.h"

// Returns the number of nodes in the list
UINT size(alist *list) {
	UINT count = 0;
	anode *temp = list->head;
	while (temp != NULL) {
		count++;
		temp = temp->next;
	}
	return count;
}

// Insert a new node with the given value at the given index.
// If index is not within range, no new node is inserted.
void insert_node_at_index(alist *list, UINT  index, UINT value) {
	if (index <= size(list)) {
		// Create new node
		anode *new_node = malloc(sizeof(struct list_node));
		new_node->value = value;
		new_node->next = NULL;

		// Insert at head
		if (index == 0) {
			new_node->next = list->head;
			list->head = new_node;
		} else {
			// Find the position
			anode *prev = list->head;
			anode *curr = prev;
			UINT i=0;
			while (i <index) {
				prev = curr;
				curr = curr->next;
				i++;
			}
			new_node->next = curr;
			prev->next = new_node;
		}
	}
}

// Delete the node at the given index if the index is
// valid.
UINT delete_node_at_index(alist *list, UINT index) {
	anode *prev = list->head;
	anode *curr = prev;
	UINT i = 0;
	while (curr != NULL && i < index) {
		prev = curr;
		curr = curr->next;
		i++;
	}
	//prev->next = curr==NULL?NULL:curr->next;
	// Delete the head
	if (i == 0) {
		curr = list->head;
		list->head = list->head->next;
		return curr->value;
	} else {
		prev->next = (curr==NULL)?NULL:curr->next;
	}

	//deallocating the node that's deleted.
	if (curr != NULL) {
		UINT value = curr->value;
		free(curr);
		curr = NULL;
		return value;
	}

	return 0;
}

// Returns the sum of all the values
// in the nodes.
UINT sum_nodes(alist *list) {
	UINT sum = 0;
	anode *temp = list->head;
	while (temp != NULL) {
		sum += temp->value;
		temp = temp->next;
	}
	return sum;
}

// Deallocate the memory for each node
// and then the list.
void free_list(alist *list) {
	anode *temp = list->head;
	while (temp != NULL) {
		anode *curr = temp;
		temp = temp->next;
		free(curr);
	}
	free(list);
}
// Deletes the node with the given value
// and adjusts the list.
void delete_node(alist *list, UINT num) {
	// prev and curr poUINT to the head node.
	anode *curr = list->head;
	anode *prev = curr;
	while (curr != NULL) {
		// Found the node with the same value as num.
		if (curr->value == num) {
			// In the case that the num is the head value.
			if (curr == list->head) {
				list->head = list->head->next;
			} else {
				prev->next = curr->next;
			}
			// deallocate current node
			free(curr);
			curr = NULL;
			break;
		}
		// Haven't found the node, advance curr and make prev the same as curr.
		prev = curr;
		curr = curr->next;
	}
}

// Creates a node with the given value and inserts
// UINTo the list. Assumes that the list is in order.
void insert_node(alist *list, UINT num) {
	anode *new_node, *node_ptr;

	// If empty, append the node.
	if (list->head == NULL)
		append_node(list, num);
	else //Find position to insert
	{
		// Allocate a new node & store num
		new_node = malloc(sizeof(struct list_node));
		new_node->value = num;
		new_node->next = NULL;

		// Initialize node_ptr to head of list
		node_ptr = list->head;
		anode *prev_node = node_ptr;

		// Find the insertion poUINT
		while (node_ptr != NULL && node_ptr->value < num) {
			prev_node = node_ptr;
			node_ptr = node_ptr->next;
		}

		// If new node is less than the first node then
		// replace the head node with the new node
		if (node_ptr == list->head) {
			new_node->next = list->head;
			list->head = new_node;
		} else {
			// Insert new_node after the prev node
			// and before the previous node's next.
			new_node->next = prev_node->next;
			prev_node->next = new_node;
		}
	}
}

// Creates a node with the given value at the end of the list.
void append_node(alist *list, UINT num) {
	anode *new_node, *node_ptr;

	// Allocate a new node & store num
	new_node = malloc(sizeof(struct list_node));
	new_node->value = num;
	new_node->next = NULL;

	// If there are no nodes in the list
	// make new_node the first node
	if (list->head == NULL)
		list->head = new_node;
	else	// Otherwise, insert new_node at end
	{
		// Initialize node_ptr to head of list
		node_ptr = list->head;

		// Find the last node in the list
		while (node_ptr->next != NULL) {
			node_ptr = node_ptr->next;
		}

		// Insert new_node as the last node
		node_ptr->next = new_node;
	}

}

// PrUINTs the values in the list.
// in the format 1.2 --> 3.4 --> NULL
void display_list(alist *list) {

	if (list != NULL) {
		// Start with the head element and check if it is empty.
		anode *temp = list->head;
		while (temp != NULL) {
			printf("%u --> ", temp->value);
			fflush(stdout);
			// Advance to the next node in the list.
			temp = temp->next;
		}
		puts("NULL");
	}
}

