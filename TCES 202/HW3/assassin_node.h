#ifndef ASSASSIN_NODE_H_INCLUDED
#define ASSASSIN_NODE_H_INCLUDED

struct assassin_node
{
    char *name;
    char *killer_name;
    struct assassin_node *next;
};

typedef struct assassin_node *anode;

#endif // ASSASSIN_NODE_H_INCLUDED
