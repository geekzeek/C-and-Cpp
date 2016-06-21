/* Zeeshan Karim, Miguel Barreto
 * TCES 203
 * Assignment	6 – Inheritance
 */

#include "list.h"
// Overloaded << operator for linked list
ostream& operator <<(ostream& out, const llist& ls)
{
    return ls.print(out);
}
// virtual helper function for objects of type llist, for use with overloaded << operator
ostream& llist::print(ostream& out) const
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
// Default constructor
llist::llist()
{
    n = 0;
    top = NULL;
    bottom = NULL;
}
// Overloaded constructor, accepts name as parameter
llist::llist(string name)
{
    node *newnode;
    newnode = new node;
    newnode->setname(name);
    newnode->setnext(NULL);
    newnode->setprev(NULL);
    top = newnode;
    bottom = newnode;
    n = 1;
}
//Adds new name to front of list, appends remainder to the next of new node.
//This function makes use of the overloaded node constructor
void llist::addFirst(string name)
{
    node *newnode;
    newnode = new node(name);
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
void llist::addLast(string name)
{
    node *newnode;
    newnode = new node;
    newnode->setname(name);
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
void llist::removeFirst()
{

    if(n==1)
    {
        delete top;
        n--;
    }
    if(n > 1)
    {
        node *temp = top;
        top = top->getnext();
        top->setprev(NULL);
        delete temp;
        n--;
    }
    else
        cout << "Nothing to Delete" << endl;
}
// removes last node from list and appends pointer to bottom
void llist::removeLast()
{
    if(n==1)
    {
        delete bottom;
        n--;
    }
    if(n > 1)
    {
        node *temp = bottom;
        bottom = bottom->getprev();
        bottom->setnext(NULL);
        delete temp;
        n--;
    }

    else
        cout << "Nothing to Delete" << endl;
}
// returns list size
int llist::listsize()
{
    return n;
}
// returns if list is empty
bool llist::isempty()
{
    if(n == 0)
        return true;
    else
        return false;
}
// destructor deletes all nodes by traversing
llist::~llist()
{
    int i;
    node *temp = top;
    for(i=0; i<n; i++)
    {
        temp = temp->getnext();
        delete top;
        top = temp;
    }

}
