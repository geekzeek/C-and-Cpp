/* Zeeshan Karim, Miguel Barreto
 * TCES 203
 * Assignment	6 – Inheritance
 */

#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include <iostream>
#include <string>
using namespace std;

//Node class declaration holds name, and pointers to previous and next nodes
//This is the basis for linked list and inherited classes
//Public functions are getters, and setters
class node
{
private:
    string name;
    node *prev;
    node *next;

public:
    node();
    node(string);
    void setname(string);
    void setprev(node*);
    void setnext(node*);
    string getname();
    node *getnext();
    node *getprev();
};

#endif // NODE_H_INCLUDED
