// Zeeshan Karim
// CES 203
// 5/6/2015
//
// Class declaration for GroceryList

#ifndef GROCERYLIST_H_INCLUDED
#define GROCERYLIST_H_INCLUDED

#include "GroceryItemOrder.h"
#include <cstring>

class GroceryList
{
    // Class stores an array of GroceryItemOrder objects
    // Counts total items in list and total price of all groceries
public:
    GroceryList();
    void add(GroceryItemOrder);
    int getlistcount();
    float totalcost();
    ~GroceryList();
private:
    GroceryItemOrder *item;
    int listcount;
};

#endif // GROCERYLIST_H_INCLUDED
