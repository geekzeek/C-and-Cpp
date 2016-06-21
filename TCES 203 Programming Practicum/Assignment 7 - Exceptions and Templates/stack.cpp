/* Zeeshan Karim, Miguel Barreto
 * TCES 203
 * Assignment	7 - Exceptions and class templates
 */

#include "stack.h"
//Adds new name to top of stack
template <class T>
void sstack<T>::push(T data)
{
	this->addFirst(data);
}

// removes name from top of stack
template <class T>
void sstack<T>::pop()
{
	this->removeFirst();
}
// overloaded << helper function for stack class
template <class T>
ostream& sstack<T>::print(ostream& out) const
{
    int i;
    node<T>* temp;
    temp = this->top;
    for(i=0; i<this->n; i++)
    {
        out << temp->getname() << endl;
        temp = temp->getnext();
    }
    return out;
}

template class sstack<string>;
