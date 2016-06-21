/*  sieve.c
    Brian Hess & Zeeshan Karim
    CES202
    Winter 2015
*/

# include <stdio.h>
# include "sieve.h"
# include "queue.h"

void compute_to(sieve, max)
{
    int i = 1
    while (i <= max)
    {
        enqueue(sieve->numlist, i)
    }

}

void report_results(*primes)
{
    int i = 0
    while(empty(primes))
    {
        printf(" %4d", dequeue(primes));
        i++;
        if(i%12 == 0)
        {
            printf("\n");
        }
    }

}
