// Zeeshan Karim
// CES 203
// 5/6/2015
//
// This file declares the class GroceryItemOrder

#ifndef GROCERYITEMORDER_H_INCLUDED
#define GROCERYITEMORDER_H_INCLUDED

using namespace std;
#include <cstring>

class GroceryItemOrder
{
    // This class stores grocery list item names, quantities, and prices
    // It has appropriate set and get functions, and can calculate total cost
public:
    GroceryItemOrder();
    GroceryItemOrder(char *, int, float);
    void setname(char *);
    void setquantity(int);
    void setppu(float);
    char *getname();
    int getquantity();
    float getppu();
    float totalcost();
    ~GroceryItemOrder();

private:
    char *name;
    int quantity;
    float ppu;

};

#endif // GROCERYITEMORDER_H_INCLUDED
