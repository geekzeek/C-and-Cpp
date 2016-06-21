/*
 * queue.h
 *
 *  Created on: Jan 31, 2015
 *      Author: mabraham
 */

#ifndef QUEUE_H_
#define QUEUE_H_
#include "list_uint.h"
#include <stdlib.h>

struct linked_queue {
	struct list *elements;
};
typedef struct linked_queue queue;

void enqueue(queue *, UINT value);
UINT dequeue(queue *);
int empty(queue *);
UINT queue_size(queue *);
void display_queue(queue *);
void free_queue(queue *);

#endif /* QUEUE_H_ */
