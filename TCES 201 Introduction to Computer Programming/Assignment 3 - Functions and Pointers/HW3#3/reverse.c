/*  Zeeshan Karim
    CES 201
    Autumn 2014
    This program prints a user inputted value with its digits reversed
*/

#include <stdio.h>
#include <stdlib.h>

int func_inverse();
int main()
{
    int n;
    printf("Enter an integer: ");
    scanf("%d",&n);
    printf("Digits reversed: %d\n", func_inverse(n));
    return 0;
}

func_inverse(int n)
{
    int inverse=0, digit=0;
    while (n>0)
    {
        inverse*=10;
        digit=n%10;
        inverse+=digit;
        n-=digit;
        n/=10;
    }
    return inverse;
}
