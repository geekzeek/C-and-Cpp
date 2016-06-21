/* Zeeshan Karim, Miguel Barreto
 * TCES 203
 * Assignment	6 – Inheritance
 */

#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include "node.h"
//Linked list class, keeps track of top and bottom of the list, along with the number of nodes in the list n
//Constructor is overloaded to allow string input which calls the node constructor
//also overloaded the << operator to allow easier printing with cout
class llist
{
protected:
    node *top;
    node *bottom;
    int n;
public:
    llist();
    llist(string);
    void addFirst(string);
    void addLast(string);
    void removeFirst();
    void removeLast();
    int listsize();
    bool isempty();
    ~llist();
    virtual ostream& print(ostream& out) const;
    friend ostream& operator << (ostream& out, const llist& ls);
};

#endif // LIST_H_INCLUDED
