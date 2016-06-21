/* Zeeshan Karim, Miguel Barreto
 * TCES 203
 * Assignment	6 – Inheritance
 */

#ifndef STACK_H_
#define STACK_H_

#include <iostream>
#include "list.h"
using namespace std;
// Inherited class stack of base class llist, provides stack functionality
class stack : public llist
{
public:
	void push(string);
	void pop();
	virtual ostream& print(ostream& out) const;
};


#endif /* STACK_H_ */
