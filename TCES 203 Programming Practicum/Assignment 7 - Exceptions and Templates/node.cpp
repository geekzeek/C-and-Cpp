/* Zeeshan Karim, Miguel Barreto
 * TCES 203
 * Assignment	7 - Exceptions and class templates
 */

#include "node.h"

//Default constructor which initiates blank variables
template <class T>
node<T>::node()
{
    data = "";
    next = NULL;
    prev = NULL;
}

//Overloaded constructor which verifies input name and initializes blank pointer members sets name of first node
template <class T>
node<T>::node(T data)
{
    this->data = data;
}
//verifies input to be at least 3 characters and sets input to name member or prints error if invalid
template <class T>
void node<T>::setname(T data)
{
    this->data = data;
}
// sets next node to input pointer
template <class T>
void node<T>::setnext(node<T> *next)
{
    this->next = next;
}
//sets previous node to input pointer
template <class T>
void node<T>::setprev(node<T> *prev)
{
    this->prev = prev;
}
// the following three functions return their respective member variables
template <class T>
T node<T>::getname()
{
    return data;
}

template <class T>
node<T> *node<T>::getnext()
{
    return next;
}

template <class T>
node<T> *node<T>::getprev()
{
    return prev;
}

template class node<string>;
