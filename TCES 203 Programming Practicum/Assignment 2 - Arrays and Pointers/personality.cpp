#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define TESTS 9
#define CATEGORY 4
#define ANSWERS 70

int counter(int k, char letter, string answers);
char letter(int k, int percent);

int main()
{
    int i, j, k,scores[TESTS][8], percents[TESTS][CATEGORY];
    float buffer;
    string names[TESTS], answers[TESTS];
    char temperament[TESTS][CATEGORY];

    // Open file and read contents
    ifstream fp ("personality.txt");
    if(!fp.is_open())
    {
        cout << "Error opening file";
        return 0;
    }
    for(i = 0; i < TESTS; i++)
    {
        getline(fp, names[i]);
        getline(fp, answers[i]);
    }
    fp.close();

    // Count answers for all tests and store into scores array
    for(i = 0; i < TESTS; i++)
    {
        int j=0;
        for(k=0; k<CATEGORY; k++)
        {
            scores[i][j++] = counter(k, 'a', answers[i]);
        }
        for(k=0; k<CATEGORY; k++)
        {
            scores[i][j++] = counter(k, 'b', answers[i]);
        }
    }

    // Calculate percentages and store into percent array
    for(i=0; i<TESTS; i++)
        for(j=0; j<CATEGORY; j++)
        {
            buffer = (float)scores[i][j+4]/(scores[i][j] + scores[i][j+4])*100;
            percents[i][j] = (int)(buffer + 0.5);
        }

    // Retrieve temperance index based on test percentages
    for(i=0; i<TESTS; i++)
        for(j=0; j<CATEGORY; j++)
            temperament[i][j] = letter(j, percents[i][j]);

    // Print results to outfile
    ofstream ofp ("personality.out");
    for(i=0; i<TESTS; i++)
    {
        ofp << names[i] << ": [";
        for(j=0; j<CATEGORY; j++)
        {
            ofp << percents[i][j];
            if(j != 3)
                ofp << ", ";
        }
        ofp << "] = ";
        for(j=0; j<CATEGORY; j++)
            ofp << temperament[i][j];
        ofp << endl;
    }
    return 0;
}

int counter(int k, char letter, string answers)
{
    int i, num = 0;
    for(i=0; i<ANSWERS/7; i++)
    {
        if(letter == 'a')
        {
            if(answers[i*7+2*k] == 'a' || answers[i*7+2*k] == 'A')
                num++;
            if(k != 0)
                if(answers[i*7+((2*k)-1)] == 'a' || answers[i*7+((2*k)-1)] == 'A')
                    num++;
        }
        if(letter == 'b')
        {
            if(answers[i*7+2*k] == 'b' || answers[i*7+2*k] == 'B')
                num++;
            if(k != 0)
                if(answers[i*7+((2*k)-1)] == 'b' || answers[i*7+((2*k)-1)] == 'B')
                    num++;
        }

    }
    return num;
}

char letter(int k, int percent)
{

    if(percent < 50)
    {
        if(k == 0)
            return 'E';
        if(k == 1)
            return 'S';
        if(k == 2)
            return 'T';
        if(k == 3)
            return 'J';
    }
    if(percent > 50)
    {
        if(k == 0)
            return 'I';
        if(k == 1)
            return 'N';
        if(k == 2)
            return 'F';
        if(k == 3)
            return 'P';
    }
    return 'X';
}
