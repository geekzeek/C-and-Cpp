// Zeeshan Karim
// CES 203
// 5/6/2015
//
// Function implementation for class GroceryItemOrder

#include "GroceryItemOrder.h"

GroceryItemOrder::GroceryItemOrder()
{
    // Default constructor, allocates memory to name char array and initializes values
    name = new char[64];
    strcpy(name, "");
    quantity = 0;
    ppu = 0;
}

GroceryItemOrder::GroceryItemOrder(char* n, int q, float p)
{
    // Overloaded constructor, allocates memory to name and initializes values to what it passed to it
    name = new char[64];
    strcpy(name, n);
    quantity = q;
    ppu = p;
}

void GroceryItemOrder::setname(char *n)
{
    // Edits name member
    strcpy(name, n);
}

void GroceryItemOrder::setquantity(int q)
{
    // Edits quantity member
    quantity = q;
}

void GroceryItemOrder::setppu(float p)
{
    // Edits price per unit member
    ppu = p;
}

char *GroceryItemOrder::getname()
{
    // Retrieves name pointer
    return name;
}

int GroceryItemOrder::getquantity()
{
    // Retrieves quantity
    return quantity;
}

float GroceryItemOrder::getppu()
{
    // Retrieves price per unit
    return ppu;
}

float GroceryItemOrder::totalcost()
{
    // Calculates total cost of items
    return (quantity*ppu);
}

GroceryItemOrder::~GroceryItemOrder()
{
    // Deallocates memory from name
    delete [] name;
    name = NULL;
}
