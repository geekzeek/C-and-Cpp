// Zeeshan Karim
// CES 203
// 5/6/2015
//
// This program tests two classes, GroceryItemOrder and GroceryList

#include <iostream>
#include <cstring>
#include <cstdio>
#include "GroceryList.h"

using namespace std;
void populateitem(GroceryItemOrder *, int);
void testoverloaded();

int main()
{
    // Main function allocates and deallocates memory, calls all other functions
    GroceryItemOrder *item;
    GroceryList itemlist;
    int n, i;
    cout << "How many items would you like to add?: ";
    cin >> n;
    item = new GroceryItemOrder[n];
    populateitem(item, n);
    for(i=0; i<n; i++)
    {
        itemlist.add(item[i]);
    }
    cout << endl << "Total items: " << itemlist.getlistcount() << endl;
    cout << "Total cost of all items: ";
    std::printf("%.2f", itemlist.totalcost());
    cout << endl;
    testoverloaded();
    delete [] item;
    item = NULL;
    return 0;
}

void populateitem(GroceryItemOrder *item, int n)
{
    // Populates array of GroceryItemOrder using user input
    int i;
    char name[64];
    int quantity;
    float ppu;
    for(i=0; i<n; i++)
    {
        cout << "Enter name: ";
        cin.ignore();
        gets(name);
        item[i].setname(name);
        cout << "Enter Quantity: ";
        cin >> quantity;
        item[i].setquantity(quantity);
        cout << "Enter Price Per Unit: ";
        cin >> ppu;
        item[i].setppu(ppu);
        cout << "Total cost: " << item[i].totalcost() << endl;
    }
}

void testoverloaded()
{
    // Tests overloaded constructor by creating new object
    char name[64];
    int quantity;
    float ppu;
    cout << endl << "Testing GroceryItemOrder overloaded constructor and get functions" << endl;
    cout << "Enter name: ";
    cin.ignore();
    gets(name);
    cout << "Enter Quantity: ";
    cin >> quantity;
    cout << "Enter Price Per Unit: ";
    cin >> ppu;
    GroceryItemOrder nitem(name, quantity, ppu);
    cout << "Data stored in new object:" << endl;
    cout << nitem.getname() << endl;
    cout << nitem.getquantity() << endl;
    cout << nitem.getppu() << endl;
}
