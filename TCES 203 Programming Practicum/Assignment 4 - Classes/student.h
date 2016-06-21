// Zeeshan Karim
// CES 203
// 4/29/2015
//
// Definition for class student


#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

#include <iostream>
#include <string>
using namespace std;

class student
{
public:
    student();
    student(string, string, int);
    student(const student&);
    void display();
    void mod_name(string);
    void mod_hobby(string);
    void mod_id(int);
    string get_name();
    string get_hobby();
    int get_id();
private:
    string name;
    string hobby;
    int id;
};

#endif // STUDENT_H_INCLUDED
