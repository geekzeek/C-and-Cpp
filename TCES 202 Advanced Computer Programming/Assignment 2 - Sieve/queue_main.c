/*
 * sieve_main.c
 *
 *  Created on: Jan 31, 2015
 *      Author: mabraham
 */

#include "queue.h"
#include <stdio.h>

/***
 * Test file to test the queue
 */

int queue_main() {
	queue *q = malloc(sizeof(struct linked_queue));
	if (empty(q)) {
		puts("queue is empty");
	}
	enqueue(q, 5);
	enqueue(q, 10);
	if (!empty(q)) {
		puts("queue is not empty");
	}
	display_queue(q);
	printf("Size is %u\n", queue_size(q));

	printf("Dequeue returned %u\n", dequeue(q));
	printf("Size after dequeue is %u\n", queue_size(q));

	display_queue(q);
	free_queue(q);
	return 0;
}
