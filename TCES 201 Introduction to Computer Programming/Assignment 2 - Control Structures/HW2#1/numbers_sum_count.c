/*  Zeeshan Karim
    CES201
    Autumn 2014
    This pro
*/

#include <stdio.h>
#include <stdlib.h>
int main()
{
    int i, pc = 0, nc = 0, pa = 0, na = 0;
    char, repeat = 'y';
    printf("Enter a number: ");
    scanf("%d", &i);

    while(repeat=='y')
    {
        if(i>0)
        {
            pc++;
            pa = ((pc - 1)pa + i) / pc;
        }

        if(i<0)
        {
            nc++;
            na = ((nc - 1)na + i) / nc;
        }

        printf("Do you want to enter another number?");
        scanf("%c", &repeat);
    }

    return(0)
}
