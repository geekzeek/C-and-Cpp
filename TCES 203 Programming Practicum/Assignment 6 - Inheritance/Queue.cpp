/* Zeeshan Karim, Miguel Barreto
 * TCES 203
 * Assignment	6 – Inheritance
 */


#include "Queue.h"
//pushes name into end of queue
void queue::push(string name)
{
	addLast(name);
}

// removes first name from list
void queue::pop()
{
	removeFirst();
}
// overloaded << operator helper function for queue class
ostream& queue::print(ostream& out) const
{
    int i;
    node* temp;
    temp = top;
    for(i=0; i<n; i++)
    {
        out << temp->getname() << endl;
        temp = temp->getnext();
    }
    return out;
}
