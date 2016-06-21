#ifndef SIEVE_H_INCLUDED
#define SIEVE_H_INCLUDED

#include "queue.h"
#include <stdio.h>

struct prime_sieve
{
    struct linked_queue *primes;
    struct linked_queue *numlist;
};
typedef struct prime_sieve sieve




#endif // SIEVE_H_INCLUDED
