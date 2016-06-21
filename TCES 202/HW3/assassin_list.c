/*
 * assassin_list.c
 *
 *  Created on: Dec 11, 2014
 *      Author: mmuppa
 *
 *  Updated by Brian G. Hess
 *
 */
#include "assassin_list.h"

/**
 Creates a new node with the given name and
 adds to the kill ring which is a circular kill ring.
 */
void list_add(alist list, char *name)
{
    //allocate, define, and allocate size for memory for nodes
    anode new_name_node, next_node_ptr;
    new_name_node = malloc(sizeof(struct assassin_node));
    new_name_node->name = malloc(sizeof(char)*(strlen(name)+1));
    strcpy(new_name_node->name, name);
    new_name_node->next = NULL;

    // If first node
    if (list->kill_ring == NULL)
    {
        list->kill_ring = new_name_node;
        list->kill_ring->next = list->kill_ring;
    }
    else
    {
        next_node_ptr = list->kill_ring;
        list_add_helper(list, next_node_ptr);
        next_node_ptr->next = new_name_node;
        new_name_node->next = list->kill_ring;
    }

}

//  This is the recursion to add names to the list
void list_add_helper(alist l, anode node_ptr)
{
    puts("#");
    if(node_ptr->next != l->kill_ring)
    {
        list_add_helper(l, node_ptr->next);
    }
}

/**
 Prints the kill ring
 */
void print_kill_ring(alist list)
{
    if (list != NULL)
    {
        anode temp = list->kill_ring;
        printf("\nCurrent Kill Ring:\n");
        print_kill_ring_helper (list, temp);
        /*do
        {
            printf("%s is stalking %s\n",temp->name,temp->next->name);
            temp = temp->next;
        }
        while (temp != list->kill_ring);*/
    }
}

void print_kill_ring_helper (alist l, anode temp)
{
    if (temp->next != l->kill_ring)
    {
        printf("%s is stalking %s\n",temp->name,temp->next->name);
        temp = temp->next;
        print_kill_ring_helper(l, temp);
    }
}

/**
 * Prints the grave yard
 */
void print_grave_yard(alist list)
{
    if (list != NULL)
    {
        anode temp = list->grave_yard;
        printf("\nCurrent Graveyard:\n");
        print_grave_yard_helper (list, temp);
        /*while (temp != NULL)
        {
            printf("%s killed by %s\n", temp->name, temp->killer_name);
            temp = temp->next;
        }*/
    }
}

void print_grave_yard_helper (alist l, anode temp)
{
    if (temp != NULL)
    {
        printf("%s killed by %s\n", temp->name, temp->killer_name);
        temp = temp->next;
        print_grave_yard_helper(l, temp);
    }
}

/**
 * Returns 1 if graveyard contains a person
 * with the given name, 0 otherwise.
 */
int grave_yard_contains(alist list, char *name)
{
    anode temp = list->grave_yard;
    return grave_yard_contains_helper(list, temp, name);
    /*while (temp != NULL)
    {
        if (strcmp(temp->name, name)==0)
        {
            return 1;
        }
        temp = temp->next;
    }
    return 0;*/
}

int grave_yard_contains_helper(alist l, anode temp, char *name)
{
    if (strcmp(temp->name, name)==0)
    {
        return 1;
    }
    else if (temp->next == l->grave_yard)
    {
        return 0;
    }
    else
    {
        temp = temp->next;
        return grave_yard_contains_helper(l, temp, name);
    }
}

/**
 * Returns 1 if kill ring contains a person
 * with the given name, 0 otherwise.
 */
int kill_ring_contains(alist list, char *name)
{
    anode temp = list->kill_ring;
    return kill_ring_contains_helper(list, temp, name);
    /*do
    {
        if (strcmp(temp->name, name)==0)
        {
            return 1;
        }
        temp = temp->next;
    }
    while (temp != list->kill_ring);
    return 0;*/
}

int kill_ring_contains_helper(alist l, anode temp, char *name)
{
    if (strcmp(temp->name, name)==0)
    {
        return 1;
    }
    else if (temp->next == l->kill_ring)
    {
        return 0;
    }
    else
    {
        temp = temp->next;
        return kill_ring_contains_helper(l, temp, name);
    }

}

/**
 * Returns 1 if game is over, only one person left in the
 * kill ring. 0 otherwise.
 */
int game_over(alist list)
{
    anode temp = list->kill_ring;
    if (strcmp(temp->name, temp->next->name)==0)
    {
        return 1;
    }
    return 0;
}

/**
 * If game is over, returns the name of the winner.
 * Otherwise, NULL.
 */
char *winner(alist list)
{
    anode temp = list->kill_ring;
    char *winner = temp->name;
    return winner;
}

/**
 * Moves the person from the kill ring into the
 * graveyard and keeps the kill ring intact.
 */
void kill_victim(alist list, char *name)
{
    anode temp_kill = list->kill_ring;
    anode prev = temp_kill;
    anode curr = prev;
    anode grave_node;

    int i;
    do
    {
        i = strcmp(curr->name, name);
        if (i == 0)
        {
            if (strcmp(list->kill_ring->name, name) == 0)
            {
                do
                {
                    prev = curr;
                    curr = curr->next;
                }
                while (curr->name != list->kill_ring->name);
                list->kill_ring = prev;
            }
            prev->next = curr->next;
            curr->next = NULL;
            if (list->grave_yard == NULL) // if nothing in the graveyard make the first thing killed the head of the list.
            {
                list->grave_yard = curr;
                list->grave_yard->killer_name = prev->name;
                curr = NULL;
            }
            else
            {
                grave_node = list->grave_yard;
                // Find the first node in the list
                while (grave_node->next != NULL)
                {
                    grave_node = grave_node->next;
                }
                // Insert new_node as the last node
                grave_node->next = curr;
                grave_node->next->killer_name = malloc(sizeof(char)*(strlen(prev->name) + 1));
                strcpy(grave_node->next->killer_name, prev->name);
                grave_node->next->killer_name = prev->name;
                curr = NULL;
            }
        }
        else
        {
            prev = curr;
            curr = curr->next;
        }
    } while (curr != temp_kill && curr != NULL);
}

/**
 * Release the memory allocated for each node, name, killer_name.
 */
void deallocate(alist list)
{
    if (list != NULL)
    {
        anode temp = list->grave_yard;
        while (temp != NULL)
        {
            free(temp->name);
            temp->name = NULL;
            if (temp->killer_name != NULL)
            {
                free(temp->killer_name);
                temp->killer_name = NULL;
            }
            anode curr = temp;
            temp = temp->next;
            free(curr);
            curr = NULL;
        }
        free(list->kill_ring->name);
        free(list->kill_ring);
        free(list);
    }

}
