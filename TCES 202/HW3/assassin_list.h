#ifndef ASSASSIN_LIST_H_INCLUDED
#define ASSASSIN_LIST_H_INCLUDED

#include "assassin_node.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct assassin_list
{
    struct assassin_node *kill_ring;
    struct assassin_node *grave_yard;
};

typedef struct assassin_list *alist;

void list_add(alist, char *);
void list_add_helper(alist, anode);
void print_kill_ring(alist);
void print_kill_ring_helper (alist l, anode temp);
void print_grave_yard(alist);
void print_grave_yard_helper (alist l, anode temp);
int game_over(alist);
char *winner(alist);
int grave_yard_contains(alist, char *);
int grave_yard_contains_helper(alist list, anode temp, char *name);
int kill_ring_contains(alist, char *);
int kill_ring_contains_helper(alist list, anode temp, char *name);
void kill_victim(alist, char *);
void deallocate(alist);

#endif // ASSASSIN_LIST_H_INCLUDED

