/*  Zeeshan Karim
    CES 201
    Autumn 2014
    This program uses a function to print a user defined quantity of Fibonacci numbers.
*/

#include <stdio.h>
#include <stdlib.h>

int fib();

int main()
{
    int m;
    printf("Enter the number of Fibonacci numbers: ");
    scanf("%d", &m);
    fib(m);
    return 0;
}

fib(int m)
{
    int fib0=0, fib1=0, fibn, counter=1;
    while(counter<=m)
    {
        if(counter==1)
        {
            fibn=1;
        }
        else
        {
            fibn = fib0 + fib1;
        }
        printf("%d: %d\n", counter, fibn);
        fib0 = fib1;
        fib1 = fibn;
        counter++;
    }
    return;
}
