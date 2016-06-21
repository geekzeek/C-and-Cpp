/*
 * sieve_main.c
 *
 *  Created on: Jan 31, 2015
 *      Author: mabraham
 */
#include "sieve.h"
#include <stdio.h>

/**
 * DO NOT MODIFY THIS CODE. WRITE YOUR MAIN TO PRELIMINARY TESTING.
 */
int main() {

	puts("This program computes all prime numbers up to a");
	puts("maximum using the Sieve of Eratosthenes.");

	int max;
	sieve *s = malloc(sizeof(struct prime_sieve));
	for (;;) {
		printf("\nMaximum n to compute (0 to quit)? ");
		fflush(stdout);
		scanf("%u", &max);
		if (max == 0)
			break;
		printf("\n");
		compute_to(s, max);
		report_results(s);
		int percent = get_count(s) * 100 / get_max(s);
		printf("Percentage of primes = %d\n", percent);
		fflush(stdout);
	}
    if (s!= NULL) {
        free(s);
        s = NULL;
    }
	return 0;
}


