#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

class stack
{
	private:
		/* data */
	public:
		stack(/* args*/);
		stack(const stack &ref);
		~stack();
		stack& operator=(const stack &ref);
};

#endif
