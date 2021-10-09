#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{

template <class T, class Container = vector<T> >
class stack
{
public:
	typedef	Container							container_type;
	typedef	typename Container::value_type		value_type;
	typedef	typename Container::size_type		size_type;
	typedef	typename Container::reference		reference;
	typedef	typename Container::const_reference	const_reference;

	explicit stack (const container_type& ctnr = container_type())
	:
		c(ctnr)
	{}

	~stack()
	{}

	stack& operator=( const stack& other ) { this->c = other->c; }

	bool				empty() const {	return (this->c.empty()); }
	size_type			size() const { return (this->c.size()); }
	value_type&			top() { return (this->c.back()); }
	const value_type&	top() const { return (this->c.back()); }
	void				push(const value_type& val) { this->c.push_back(val); }
	void				pop() { this->c.pop_back(); }

protected:
	container_type	c;

template <class Tn, class Containern>
	friend bool operator== (const stack<Tn,Containern>& lhs, const stack<Tn,Containern>& rhs);
template <class Tn, class Containern>
	friend bool operator<  (const stack<Tn,Containern>& lhs, const stack<Tn,Containern>& rhs);

};


template <class Tn, class Containern>
	bool operator== (const stack<Tn,Containern>& lhs, const stack<Tn,Containern>& rhs) { return (lhs.c == rhs.c); }
template <class Tn, class Containern>
	bool operator<  (const stack<Tn,Containern>& lhs, const stack<Tn,Containern>& rhs) { return (lhs.c < rhs.c); }
template <class Tn, class Containern>
	bool operator!= (const stack<Tn,Containern>& lhs, const stack<Tn,Containern>& rhs) { return !(lhs == rhs); }
template <class Tn, class Containern>
	bool operator<= (const stack<Tn,Containern>& lhs, const stack<Tn,Containern>& rhs) { return !(rhs < lhs); }
template <class Tn, class Containern>
	bool operator>  (const stack<Tn,Containern>& lhs, const stack<Tn,Containern>& rhs) { return (rhs < lhs); }
template <class Tn, class Containern>
	bool operator>= (const stack<Tn,Containern>& lhs, const stack<Tn,Containern>& rhs) { return !(lhs < rhs); }

}

#endif
