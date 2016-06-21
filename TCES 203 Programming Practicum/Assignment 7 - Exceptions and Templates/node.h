/* Zeeshan Karim, Miguel Barreto
 * TCES 203
 * Assignment	7 - Exceptions and class templates
 */

#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include <iostream>
#include <string>
using namespace std;

//Node class declaration holds name, and pointers to previous and next nodes
//This is the basis for linked list and inherited classes
//Public functions are getters, and setters
template <class T>
class node
{
private:
    T data;
    node<T> *prev;
    node<T> *next;

public:
    node();
    node(T);
    void setname(T);
    void setprev(node<T>*);
    void setnext(node<T>*);
    T getname();
    node<T> *getnext();
    node<T> *getprev();
};

#endif // NODE_H_INCLUDED
