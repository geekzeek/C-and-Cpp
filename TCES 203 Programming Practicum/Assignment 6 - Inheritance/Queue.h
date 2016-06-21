/* Zeeshan Karim, Miguel Barreto
 * TCES 203
 * Assignment	6 – Inheritance
 */


#ifndef QUEUE_H_
#define QUEUE_H_

#include <iostream>
#include "list.h"
using namespace std;
//Inherited class queue with base class llist, provides queue functionality
class queue : public llist
{
public:
	void push(string);
	void pop();
	virtual ostream& print(ostream& out) const;
	//overload <<, say if it's from stack or queue
};

#endif /* QUEUE_H_ */
