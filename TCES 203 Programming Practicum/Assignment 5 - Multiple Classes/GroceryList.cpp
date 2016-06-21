// Zeeshan Karim
// CES 203
// 5/6/2015
//
// Function implementation for class GroceryList

#include "GroceryList.h"

GroceryList::GroceryList()
{
    // Default constructor, allocates memory for 10 GroceryItemOrder array
    item = new GroceryItemOrder[10];
    listcount = 0;
}

void GroceryList::add(GroceryItemOrder nitem)
{
    // Adds GroceryItemOrder passed to function to the array
    if(listcount < 10)
    {
        item[listcount].setname(nitem.getname());
        item[listcount].setquantity(nitem.getquantity());
        item[listcount].setppu(nitem.getppu());
        listcount++;
    }
}

int GroceryList::getlistcount()
{
    // Retrieves number of items in list
    return listcount;
}

float GroceryList::totalcost()
{
    // Calculates total cost
    int i;
    float total;
    for(i=0; i<listcount; i++)
    {
        total += (item[i].getquantity() * item[i].getppu());
    }
    return total;
}

GroceryList::~GroceryList()
{
    // Default destructor, deletes object array memory
    delete [] item;
    item = NULL;
}
