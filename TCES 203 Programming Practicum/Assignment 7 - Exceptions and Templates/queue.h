/* Zeeshan Karim, Miguel Barreto
 * TCES 203
 * Assignment	7 - Exceptions and class templates
 */


#ifndef QUEUE_H_
#define QUEUE_H_

#include <iostream>
#include "list.h"
using namespace std;
//Inherited class queue with base class llist, provides queue functionality
template <class T>
class qqueue : public llist<T>
{
public:
	void push(T);
	void pop();
	virtual ostream& print(ostream& out) const;
	//overload <<, say if it's from stack or queue
};

#endif /* QUEUE_H_ */
