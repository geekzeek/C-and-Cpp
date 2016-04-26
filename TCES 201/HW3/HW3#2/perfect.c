/*  Zeeshan Karim
    CES 201
    Autumn 2014
    This program lists perfect numbers and their factors from 1 to 10000.
 */

#include <stdio.h>
int perfect(int);
void list_perfect(int);

int main()
{
    int i;
    printf("Here are the perfect numbers between 1 and 10000");
    for (i=2; i<10000; i++)
    {
        if (perfect(i))
        {
            list_perfect(i);
        }
    }
    return 0;
}

/*
Returns whether a given number is perfect
*/
int perfect(int number)
{
    int i, perf=0, value;
    for(i=1; i<number; i++)
    {
        if (number%i==0)
        {
            perf+=i;
        }
    }
    if(number==perf)
    {
        value=1;
    }
    else
    {
        value=0;
    }
    return value;
}

/*
Lists the perfect number's factors
Example: 6 = 1 + 2 + 3
*/
void list_perfect(int number)
{
    int i;
    printf("\n%d = ", number);
    for(i=1; i<number; i++)
        {
        if(number%i==0)
            {
            if(i==1)
                {
                printf("%d ", i);
                }
            else
                {
                printf("+ %d ", i);
                }
            }
        }
    return;
}
