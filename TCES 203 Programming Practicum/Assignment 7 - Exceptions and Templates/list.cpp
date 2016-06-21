/* Zeeshan Karim, Miguel Barreto
 * TCES 203
 * Assignment	7 - Exceptions and class templates
 */

#include "list.h"

// Overloaded << operator for linked list
template <class T>
inline ostream& operator <<(ostream& out, const llist<T>& ls)
{
    return ls.print(out);
}
// virtual helper function for objects of type llist, for use with overloaded << operator
template <class T>
ostream& llist<T>::print(ostream& out) const
{
    int i;
    node<T>* temp;
    temp = top;
    for(i=0; i<n; i++)
    {
        out << temp->getname() << endl;
        temp = temp->getnext();
    }
    return out;
}
// Default constructor
template <class T>
llist<T>::llist()
{
    n = 0;
    top = NULL;
    bottom = NULL;
}
// Overloaded constructor, accepts name as parameter
template <class T>
llist<T>::llist(T data)
{
    node<T> *newnode;
    newnode = new node<T>;
    newnode->setname(data);
    newnode->setnext(NULL);
    newnode->setprev(NULL);
    top = newnode;
    bottom = newnode;
    n = 1;
}
//Adds new name to front of list, appends remainder to the next of new node.
//This function makes use of the overloaded node constructor
template <class T>
void llist<T>::addFirst(T data)
{
    node<T> *newnode;
    newnode = new node<T>(data);
    newnode->setnext(top);
    newnode->setprev(NULL);
    if(top != NULL)
        top->setprev(newnode);
    if(top == NULL)
        bottom = newnode;
    top = newnode;
    n++;
}
//Adds new name to back of list, appends remainder to the next of new node.
//This function makes use of the node default constructor
template <class T>
void llist<T>::addLast(T data)
{
    node<T> *newnode;
    newnode = new node<T>;
    newnode->setname(data);
    newnode->setprev(bottom);
    newnode->setnext(NULL);
    if(bottom != NULL)
        bottom->setnext(newnode);
    if(bottom == NULL)
        top = newnode;
    bottom = newnode;

    n++;

}
// removes first node from list and appends remainder to the pointer for top
template <class T>
void llist<T>::removeFirst()
{

    if(n==1)
    {
        delete top;
        n--;
    }
    if(n > 1)
    {
        node<T> *temp = top;
        top = top->getnext();
        top->setprev(NULL);
        delete temp;
        n--;
    }
    else
        throw string("Nothing to Delete");
}
// removes last node from list and appends pointer to bottom
template <class T>
void llist<T>::removeLast()
{
    if(n==1)
    {
        delete bottom;
        n--;
    }
    if(n > 1)
    {
        node<T> *temp = bottom;
        bottom = bottom->getprev();
        bottom->setnext(NULL);
        delete temp;
        n--;
    }

    else
        throw string("Nothing to Delete");
}
// returns list size
template <class T>
int llist<T>::listsize()
{
    return n;
}
// returns if list is empty
template <class T>
bool llist<T>::isempty()
{
    if(n == 0)
        return true;
    else
        return false;
}
// destructor deletes all nodes by traversing
template <class T>
llist<T>::~llist()
{
    int i;
    node<T> *temp = top;
    for(i=0; i<n; i++)
    {
        temp = temp->getnext();
        delete top;
        top = temp;
    }

}

template class llist<string>;
