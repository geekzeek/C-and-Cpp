/* Zeeshan Karim, Miguel Barreto
 * TCES 203
 * Assignment	7 - Exceptions and class templates
 * This program tests inheritance with a linked list class as the base class for queue and stack classes
 * Additionally it makes use of exceptions and class templates, so it can easil
 */
#include <iostream>
#include "list.h"
#include "stack.h"
#include "queue.h"

using namespace std;

void printmenu();
void testll();
void teststack();
void testqueue();
//calls main menu for testing classes
int main()
{
    int response;
    do
    {
        printmenu();
        cin >> response;
        switch(response)
        {
        case 1:
            {
                testll();
                break;
            }
        case 2:
            {
                teststack();
                break;
            }
        case 3:
            {
                testqueue();
                break;
            }
        }
    }while(response > 0 && response < 4);
    return 0;
}
//prints menu options
void printmenu()
{
    cout << "What would you like to do?" << endl;
    cout << "\t1) Test linked list" << endl;
    cout << "\t2) Test stack " << endl;
    cout << "\t3) Test Queue" << endl;
    cout << "\t4) Exit" << endl;
    cout << "Response: ";
}
// provides functionality for testing llist class
void testll()
{
    llist<string> newlist;
    int response;
    string name;
    do
    {
        cout << endl;
        cout << "1) Add name to front" << endl;
        cout << "2) Add name to back" << endl;
        cout << "3) Remove from front" << endl;
        cout << "4) Remove from back" << endl;
        cout << "5) Print" << endl;
        cout << "6) Exit" << endl;
        cout << "Response: ";
        cin >> response;
        cout << endl;
        switch (response)
        {
        case 1:
            {
                cout << "Enter name: ";
                cin >> name;
                newlist.addFirst(name);
                break;
            }
        case 2:
            {
                cout << "Enter name: ";
                cin >> name;
                newlist.addLast(name);
                break;
            }
        case 3:
            {
                try
                {
                    newlist.removeFirst();
                    break;
                }
                catch(string c)
                {
                    cout << c << endl;
                    break;
                }
            }
        case 4:
            {
                try
                {
                    newlist.removeLast();
                    break;
                }
                catch(string c)
                {
                    cout << c << endl;
                    break;
                }
            }
        case 5:
            {
//                cout << newlist;
                break;
            }
        }
    }while(response > 0 && response < 6);
}
// provides functionality for testing stack class
void teststack()
{
    int i;
    sstack<string> newstack;
    string buffer;
    do
    {
        cout << endl << "1) Push name" << endl;
        cout << "2) Pop name" << endl;
        cout << "3) Print" << endl;
        cout << "4) Exit" << endl;
        cout << "Response: ";
        cin >> i;
        switch(i)
        {
        case 1:
            {
                cout << "Enter name: ";
                cin >> buffer;
                newstack.push(buffer);
                break;
            }
        case 2:
            {
                try
                {
                    newstack.pop();
                    break;
                }
                catch(string c)
                {
                    cout << c << endl;
                    break;
                }
            }
        case 3:
            {
//                cout << newstack;
            }
        }
    }while(i<4 && i > 0);
}
// provides functionality for testing queue class
void testqueue()
{
    int i;
    qqueue<string> newqueue;
    string buffer;
    do
    {
        cout << endl << "1) Enqueue name" << endl;
        cout << "2) Dequeue" << endl;
        cout << "3) Print" << endl;
        cout << "4) Exit" << endl;
        cout << "Response: ";
        cin >> i;
        cout << endl;
        switch(i)
        {
        case 1:
            {
                cout << "Enter name: ";
                cin >> buffer;
                newqueue.push(buffer);
                break;
            }
        case 2:
            {
                try
                {
                    newqueue.pop();
                    break;
                }
                catch(string c)
                {
                    cout << c << endl;
                    break;
                }

            }
        case 3:
            {
//                cout << newqueue;
                break;
            }

        }
    }while(i>0 && i<4);
}
