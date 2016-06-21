/* Zeeshan Karim, Miguel Barreto
 * TCES 203
 * Assignment	7 - Exceptions and class templates
 */


#include "queue.h"
//pushes name into end of queue
template <class T>
void qqueue<T>::push(T data)
{
	this->addLast(data);
}

// removes first name from list
template <class T>
void qqueue<T>::pop()
{
	this->removeFirst();
}
// overloaded << operator helper function for queue class
template <class T>
ostream& qqueue<T>::print(ostream& out) const
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

template class qqueue<string>;
