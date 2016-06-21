// Zeeshan Karim
// 4/22/2015
// 203
// Assignment #1
//
// student.h

#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED
#include <iostream>
#include <string>
using namespace std;

struct student {
    // Struct containing student data
    string name;
    string hobby;
    int id;
};

// Function Prototypes
void populate(const int, student*);
void menu(const int, student*);
void print_data(const int, const student*);
void print_data(const int, const student);
void edit_data(const int, student*);

#endif // STUDENT_H_INCLUDED
