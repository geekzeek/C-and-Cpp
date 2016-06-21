/* Zeeshan Karim, Miguel Barreto
 * TCES 203
 * Assignment	7 - Exceptions and class templates
 */

#ifndef STACK_H_
#define STACK_H_

#include <iostream>
#include "list.h"
using namespace std;
// Inherited class stack of base class llist, provides stack functionality
template <class T>
class sstack : public llist<T>
{
public:
	void push(T);
	void pop();
	virtual ostream& print(ostream& out) const;
};


#endif /* STACK_H_ */
