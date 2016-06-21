/*  Zeeshan Karim
    CES201
    Autumn 2014
    This programs delivers a positive and negative count and sum of values inputted by the user
*/

#include <stdio.h>
#include <stdlib.h>
int main()
{
    int i, pc = 0, nc = 0, ps = 0, ns = 0;
    char repeat;

    do
    {
    printf("Enter a number: ");
    scanf("%d", &i);

        if(i>0)
        {
            pc++;
            ps += i;
        }

        if(i<0)
        {
            nc++;
            ns += i;
        }

        getchar();
        printf("Do you want to enter another number?");
        scanf("%c", &repeat);

    }while(repeat == 'y');

    printf("\nYou entered %d positive numbers and their sum is %d", pc, ps);
    printf("\nYou entered %d negative numbers and their sum is %d", nc, ns);

return(0);
}

