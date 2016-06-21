/*
 * queue.c
 *
 *  Created on: Jan 31, 2015
 *      Author: mabraham
 */
#include "queue.h"
#include <stdio.h>

// Inserts at the end of the queue.
void enqueue(queue *q, UINT value) {
	if (q->elements == NULL) {
		q->elements = malloc(sizeof(struct list));
	}
	append_node(q->elements, value);
}

// Returns the first element of the queue.
UINT dequeue(queue *q) {
	return delete_node_at_index(q->elements, 0);
}

// Returns 1 if queue is empty, 0 otherwise.
int empty(queue *q) {
	if (q->elements == NULL) {
		return 1;
	}
	return 0;
}

// Returns the size of the queue
UINT queue_size(queue *q) {
	return size(q->elements);
}

void display_queue(queue *q) {
	printf("front : ");
	display_list(q->elements);
}

void free_queue(queue *q) {
	if (q->elements != NULL) {
		free_list(q->elements);
	}
	free(q);
	q = NULL;
}
