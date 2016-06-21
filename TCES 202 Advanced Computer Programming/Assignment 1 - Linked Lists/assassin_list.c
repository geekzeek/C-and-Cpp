/*
 * assassin_list.c
 *
 *  Created on: Dec 11, 2014
 *      Author: mmuppa
 *
 */
#include "assassin_list.h"

/**
 Creates a new node with the given name and
 adds to the kill ring which is a circular kill ring.
 */
void list_add(alist list, char *name)
    {
        struct assassin_node *new_node, *node_ptr;
        if(list->kill_ring == NULL)//if kill_ring is empty create head
        {
            new_node = malloc(sizeof(anode));//allocate memory to new node and assign values
            new_node->name = name;
            new_node->killer_name = NULL;
            new_node->next = NULL;
            list->kill_ring = new_node;//assign new node to kill_list head
        }
        else//if head exists, append node to end of list
        {
            new_node = malloc(sizeof(anode));//allocate memory to new node, assign values
            new_node->name = name;
            new_node->killer_name = NULL;
            new_node->next = list->kill_ring;//assign new node next to kill_ring head, for circular list
            node_ptr = list->kill_ring;//iterate through kill_ring to find last entry
            while(node_ptr->next != NULL)
            {
                node_ptr = node_ptr->next;
            }
            node_ptr->next = new_node;

        }
    }

/**
 Prints the kill ring
 */
void print_kill_ring(alist list) {
}

/**
 * Prints the grave yard
 */
void print_grave_yard(alist list) {
}

/**
 * Returns 1 if graveyard contains a person
 * with the given name, 0 otherwise.
 */
int grave_yard_contains(alist list, char *name) {
}

/**
 * Returns 1 if kill ring contains a person
 * with the given name, 0 otherwise.
 */
int kill_ring_contains(alist list, char *name) {
}
/**
 * Returns 1 if game is over, only one person left in the
 * kill ring. 0 otherwise.
 */
int game_over(alist list) {
}

/**
 * If game is over, returns the name of the winner.
 * Otherwise, NULL.
 */
char *winner(alist list) {
}

/**
 * Moves the person from the kill ring into the
 * graveyard and keeps the kill ring intact.
 */
void kill_victim(alist list, char *name) {
}

/**
 * Release the memory allocated for each node, name, killer_name.
 */
void deallocate(alist list) {
}
