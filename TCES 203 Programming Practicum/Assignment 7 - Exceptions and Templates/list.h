/* Zeeshan Karim, Miguel Barreto
 * TCES 203
 * Assignment	7 - Exceptions and class templates
 */

#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include "node.h"

template <class T> class llist;
template <class T> ostream& operator << (ostream& out, const llist<T>& ls);
//Linked list class, keeps track of top and bottom of the list, along with the number of nodes in the list n
//Constructor is overloaded to allow string input which calls the node constructor
//also overloaded the << operator to allow easier printing with cout
template <class T>
class llist
{
protected:
    node<T> *top;
    node<T> *bottom;
    int n;
public:
    llist();
    llist(T);
    void addFirst(T);
    void addLast(T);
    void removeFirst();
    void removeLast();
    int listsize();
    bool isempty();
    ~llist();
    virtual ostream& print(ostream& out) const;
    friend ostream& operator << <> (ostream& out, const llist<T>& ls);
};

#endif // LIST_H_INCLUDED
