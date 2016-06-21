// Zeeshan Karim
// CES 203
// 4/29/2015
//
// Function implementation for class student

#include "student.h"

student::student()
{
    // Default constructor, initializes values
    //name = "";
    //hobby = "";
    //id = 0;
}

student::student(string n, string h, int i)
{
    // Overloaded constructor, initializes values to what is passed to it
    name = n;
    hobby = h;
    id = i;
}

student::student(const student &obj)
{
    // Copy constructor, copies values from object sent to it to new object
    name = obj.name;
    hobby = obj.hobby;
    id = obj.id;
}

void student::display()
{
    // Displays all student data
    cout << endl << "Name:  " << name << endl;
    cout << "Hobby: " << hobby << endl;
    cout << "ID:    " << id << endl;
}

void student::mod_name(string n)
{
    // Edits student name
    name = n;
}
void student::mod_hobby(string h)
{
    // Edits student hobby
    hobby = h;
}

void student::mod_id(int i)
{
    // Edits ID, only used when first inputting data
    id = i;
}

string student::get_name()
{
    // Returns student name
    return name;
}

string student::get_hobby()
{
    // Returns student hobby
    return hobby;
}

int student::get_id()
{
    // Returns student ID
    return id;
}

