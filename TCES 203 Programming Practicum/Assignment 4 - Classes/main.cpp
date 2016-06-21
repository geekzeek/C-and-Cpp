// Zeeshan Karim
// CES 203
// 4/29/2015
//
// This program uses an object array to store and display student data

#include "student.h"

// Function prototypes
void setdata(student *, int);
void menu(student *, int);
int getindex(student *, int);
void editdata(student *, int);
void copyconst(student *, int);
void overconst(student *, int);
void pressenter();

int main()
{
    // Allocates memory to object array, calls functions, deletes data
    int n;
    student *data;
    cout << "Enter number of students: ";
    cin >> n;
    data = new student[n];
    setdata(data, n);
    menu(data, n);
    delete [] data;
    return 0;
}

void setdata(student *data, int n)
{
    // Adds data to array at start
    int i, id;
    string name, hobby;
    for(i=0; i<n; i++)
    {
        cout << endl << "Enter student " << i+1 << " data:" << endl;
        cout << "Name:  ";
        cin.ignore();
        getline(cin, name);
        cout << "Hobby: ";
        getline(cin, hobby);
        cout << "ID:    ";
        cin >> id;
        data[i].mod_name(name);
        data[i].mod_hobby(hobby);
        data[i].mod_id(id);
    }
}

void menu(student *data, int n)
{
    // Menu calls all functions, and contains some basic displaying code
    int input, i, index;
    do
    {
        cout << endl;
        pressenter();
        cout << "What would you like to do?" << endl;
        cout << "1) Print all data" << endl;
        cout << "2) Print one student's data" << endl;
        cout << "3) Edit student data" << endl;
        cout << "4) Test copy constructor" << endl;
        cout << "5) Test overloaded constructor" << endl;
        cout << "6) Get student name" << endl;
        cout << "7) Get student hobby" << endl;
        cout << "8) Get student ID" << endl;
        cout << "9) Exit" << endl;
        cout << "Selection: ";
        cin >> input;

        switch(input)
        {
        case 1:
            {
                // Prints all data
                for(i=0; i<n; i++)
                    data[i].display();
                break;
            }
        case 2:
            {
                // Prints data at index
                index = getindex(data, n);
                if(input != -1)
                    data[index].display();
                break;
            }
        case 3:
            {
                editdata(data, n);
                break;
            }
        case 4:
            {
                copyconst(data, n);
                break;
            }
        case 5:
            {
                overconst(data, n);
                break;
            }
        case 6:
            {
                // prints name
                index = getindex(data, n);
                if(index != -1)
                    cout << endl << data[index].get_name() << endl;
                break;
            }
        case 7:
            {
                // prints hobby
                index = getindex(data, n);
                if(index != -1)
                    cout << endl << data[index].get_hobby() << endl;
                break;
            }
        case 8:
            {
                // prints ID
                cout << endl << "Enter student index (0-" << n-1 << ") :";
                cin >> index;
                if(index < n && index > -1)
                    cout << endl << data[index].get_id() << endl;
                break;
            }
        }

    }while(input != 9);
}

int getindex(student *data, int n)
{
    // Finds student index based on id
    int i, id, success = 0;
    cout << endl << "Enter student ID: ";
    cin >> id;
    for(i=0; i<n; i++)
    {
        if(data[i].get_id() == id)
        {
            success = 1;
            return i;
        }
    }
    if(success == 0)
        cout << "Student not found" << endl;
    return -1;
}

void editdata(student *data, int n)
{
    // Used to edit student data
    int i;
    string buffer;
    i = getindex(data, n);
    if(i != -1)
    {
        data[i].display();
        cout << endl << "New name: ";
        cin.ignore();
        getline(cin, buffer);
        data[i].mod_name(buffer);
        cout << "New hobby: ";
        getline(cin, buffer);
        data[i].mod_hobby(buffer);
    }

}

void copyconst(student *data, int n)
{
    // Function for testing copy constructor
    int i;
    cout << endl << "Enter student ID to copy to new object: ";
    i = getindex(data, n);
    if(i != -1)
    {
        student obj = data[i];
        cout << endl << "Displaying data from original object: " << endl;
        data[i].display();
        cout << endl << "Displaying data from copied object: " << endl;
        obj.display();
    }
}

void overconst(student *data, int n)
{
    // Function for testing overloaded constructor
    int id;
    string name, hobby;
    cout << endl << "Creating new object using overloaded constructor:" << endl;
    cout << "Name:  ";
    cin.ignore();
    getline(cin, name);
    cout << "Hobby: ";
    getline(cin, hobby);
    cout << "ID:    ";
    cin >> id;
    student obj(name, hobby, id);
    cout << endl << "Displaying new object data: " << endl;
    obj.display();
}

void pressenter()
{
    // Function used to space apart functions in ui
    string x;
    cout << "Press enter to continue" << endl;
    cin.ignore();
    getline(cin, x);
}
