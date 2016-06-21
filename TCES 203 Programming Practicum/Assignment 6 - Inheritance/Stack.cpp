/* Zeeshan Karim, Miguel Barreto
 * TCES 203
 * Assignment	6 – Inheritance
 */

#include "Stack.h"
//Adds new name to top of stack
void stack::push(string name)
{
	addFirst(name);
}

// removes name from top of stack
void stack::pop()
{
	removeFirst();
}
// overloaded << helper function for stack class
ostream& stack::print(ostream& out) const
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

