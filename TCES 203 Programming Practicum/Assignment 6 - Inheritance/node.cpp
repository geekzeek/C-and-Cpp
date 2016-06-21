/* Zeeshan Karim, Miguel Barreto
 * TCES 203
 * Assignment	6 – Inheritance
 */

#include "node.h"

//Default constructor which initiates blank variables
node::node()
{
    name = "";
    next = NULL;
    prev = NULL;
}

//Overloaded constructor which verifies input name and initializes blank pointer members sets name of first node
node::node(string name)
{
    if (name.length() < 4)
    {
        cout << "Invalid name length";
    }
    else
    {
        this->name = name;
    }
}
//verifies input to be at least 3 characters and sets input to name member or prints error if invalid
void node::setname(string name)
{
    if(name.length() < 3)
    {
        cout << "Invalid name length";
    }
    else
    {
        this->name = name;
    }
}
// sets next node to input pointer
void node::setnext(node *next)
{
    this->next = next;
}
//sets previous node to input pointer
void node::setprev(node *prev)
{
    this->prev = prev;
}
// the following three functions return their respective member variables
string node::getname()
{
    return name;
}

node *node::getnext()
{
    return next;
}

node *node::getprev()
{
    return prev;
}


