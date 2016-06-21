// Zeeshan Karim
// 4/8/2015
// 203
// Assignment #1
//
// This program compares two students based on their SAT or ACT scores, and GPA

#include <iostream>

using namespace std;

float calculate(int);
float SAT();
float ACT();
void intro();
void comp(float score1, float score2);

int main()
{
    //The main function calls the helper functions in sequence
    float score1, score2;
    intro();
    score1 = calculate(1);
    score2 = calculate(2);
    comp(score1, score2);
    return 0;
}

float calculate(int app)
{
    //Determines which student is being evaluated and calls appropriate function
    int test;
    if(app == 1)
        cout << "Information for the first applicant:" << endl;

    if(app == 2)
        cout << "Information for the second applicant:" << endl;

    cout << "\tdo you have 1) SAT scores or 2) ACT scores? ";
    cin >> test;

    if (test == 1)
        return SAT();

    if (test == 2)
        return ACT();
}

float SAT()
{
    //Calculates student score based on SAT and returns it
    int math, verbal;
    float gpa, gpamax;

    cout << "\tSAT math? ";
    cin >> math;
    cout << "\tSAT verbal? ";
    cin >> verbal;
    cout << "\tactual GPA? ";
    cin >> gpa;
    cout << "\tmax GPA? ";
    cin >> gpamax;

    return ((2*verbal+math)/24 + (gpa/gpamax)*100);
}

float ACT()
{
    //Calculates student score based on ACT and returns it
    int english, math, reading, science;
    float gpa, gpamax;

    cout << "\tACT English? ";
    cin >> english;
    cout << "\tACT math? ";
    cin >> math;
    cout << "\tACT reading? ";
    cin >> reading;
    cout << "\tACT science? ";
    cin >> science;
    cout << "\tactual GPA? ";
    cin >> gpa;
    cout << "\tmax GPA? ";
    cin >> gpamax;

    return ((2*reading + math + english + science)/1.8 + (gpa/gpamax)*100);
}

void intro()
{
    //Prints introductory information for user
    cout << "This program compares two applicants to" << endl;
    cout << "determine which one seems like the stronger" << endl;
    cout << "applicant. For each candidate I will need" << endl;
    cout << "either SAT or ACT scores plus a weighted GPA." << endl << endl;
}

void comp(float score1, float score2)
{
    //Compares the two scores and displays results
    cout << endl;
    cout << "First applicant overall score  = " << score1 << endl;
    cout << "Second applicant overall score = " << score2 << endl;

    if(score1>score2)
        cout << "The first applicant seems to be better" << endl;

    if(score2>score1)
        cout << "The second applicant seems to be better" << endl;

    if(score1 == score2)
        cout << "The two applicants seem to be equal" << endl;
}
