// Zeeshan Karim
// 4/22/2015
// 203
// Assignment #3
//
// This program stores & displays student data using a dynamically allocated struct

#include "student.h"

int main()
{
    // Allocates memory to array and calls populate, then menu function
    student *student_array;
    int n;

    cout << "Enter number of students: ";
    cin >> n;
    student_array = new student[n];

    populate(n, student_array);
    menu(n, student_array);
    cout << "Closing program and deleting data" << endl;
    delete [] student_array;
    return 0;
}

void populate(const int n, student *student_array)
{
    // Gets student data from user and stores into student_array
    int i;
    for(i = 0; i < n; i++)
    {
        cout << "Enter student " << i+1 << " name:  ";
        cin.ignore();
        getline(cin, student_array[i].name);
        cout << "Enter student " << i+1 << " hobby: ";
        getline(cin, student_array[i].hobby);
        cout << "Enter student " << i+1 << " ID:    ";
        cin >> student_array[i].id;
        cout << endl;
    }
}

void menu(const int n, student *student_array)
{
    //Main menu to choose functions, or to exit
    int selection, i;
    do
    {
        cout << "What would you like to do?" << endl;
        cout << "1) Print all student data" << endl;
        cout << "2) Print one student's data" << endl;
        cout << "3) Edit student data" << endl;
        cout << "4) Exit" << endl;
        cout << "Selection: ";
        cin >> selection;
        cout << endl;

        switch(selection)
        {
        case 1:
            print_data(n, student_array);
            break;
        case 2:
            cout << "Which student's data would you like to print?: ";
            cin >> i;
            if(i>=0 && i<=n)
                print_data(i, student_array[i-1]);
            else
                cout << "Invalid selection" << endl << endl;
            break;
        case 3:
            edit_data(n, student_array);
            break;
        }
    }while(selection != 4);
}

void print_data(const int n, const student *student_array)
{
    // Prints all data stored in student_array
    int i;
    for(i=0; i<n; i++)
    {
        cout << "Student " << i+1 << ":" << endl;
        cout << "Name:   " << student_array[i].name << endl;
        cout << "Hobby:  " << student_array[i].hobby << endl;
        cout << "ID:     " << student_array[i].id << endl;
        cout << endl;
    }
}

void print_data(const int i, const student selection)
{
    // Prints single student data, as passed to it
    cout << "Student " << i << ":" << endl;
    cout << "Name:   " << selection.name << endl;
    cout << "Hobby:  " << selection.hobby << endl;
    cout << "ID:     " << selection.id << endl;
    cout << endl;
}

void edit_data(const int n, student *student_array)
{
    // Finds student based on id, and edits name and hobby data
    int id, i, index = -1;
    char selection;

    cout << "Enter the ID of the student to edit: ";
    cin >> id;
    for(i=0; i<n; i++)
    {
        if(student_array[i].id == id)
            index = i;
    }
    if(index != -1)
    {
        print_data(index+1, student_array[index]);
        cout << "Edit name? (y/n): ";
        cin >> selection;
        if(selection == 'y')
        {
            cout << "Enter new name: ";
            cin.ignore();
            getline(cin, student_array[index].name);
        }

        cout << "Edit hobby? (y/n): ";
        cin >> selection;
        if(selection == 'y')
        {
            cout << "Enter new hobby: ";
            cin.ignore();
            getline(cin, student_array[index].hobby);
        }
        cout << endl << "Updated student data:" << endl;
        print_data(index+1, student_array[index]);
        }
    else
        cout << "Student ID not found" << endl << endl;
}
