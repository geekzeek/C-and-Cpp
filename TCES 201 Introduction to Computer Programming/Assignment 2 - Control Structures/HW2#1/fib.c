/*  Zeeshan Karim
    CES201
    Autumn 2014
    This program displays n digits of the Fibonacci sequence as set by the user
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int input, counter = 0, odd;
    double product;

    product=1;

    printf("Enter the maximum value: ");
    scanf("%d", &input);

    do
    {
       odd =  2*counter + 1;
       product *= odd;

    }while(odd<=input);

    printf("Product of odd integers from 1 to %d is %d", input, product);
    return(0);

}
