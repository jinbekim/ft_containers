#include <vector>
// #include "vector.hpp"
#include "stack.hpp"
#include <list>
#include <iostream>

using namespace std;

class	node
{
	private:
		int		val;
		node*	next;
		node*	prev;

	public:
		node(int val);
		~node();
		node(const node& n);
		node&	operator=(const node& n);
		int	v();
		node* n();
		node* p();
};

node::node(int val)
{
	this->val = val;
	next = this;
	prev = this;
}

node::~node() {}

node::node(const node& n)
{
	this->val = n.val;
	next = this;
	prev = this;
}

node&	node::operator=(const node& n)
{
	this->val = n.val;
	next = this;
	prev = this;
	return (*this);
}

int	node::v() {return this->val;}

node*	node::n() {return this->next;}
node*	node::p() {return this->prev;}

int main()
{
	// vector<int> v(3,3);
	// v.reserve(5);
	// cout << "capa :"  << v.capacity() <<endl;
	// cout << "size :"  << v.size() <<endl;
	// v.insert(v.begin(), 3);
	// // v.push_back(3);
	// // v.push_back(3);
	// cout << "capa :"  << v.capacity() <<endl;
	// cout << "size :"  << v.size() <<endl;
	ft::stack<int> st1;
	ft::stack<int> st2;

	std::cout<< (st1 == st2) << std::endl;
	// v.reserve(5);

	// cout << "capa :"  << v.capacity() <<endl;
	// cout << "size :"  << v.size() <<endl;

	// v.resize(5);
	// for(vector<int>::iterator it = v.begin(); it != v.end(); ++it)
	// 	cout << *it <<endl;

	// cout << "capa: " << v.capacity() <<endl;
	// cout << "size :"  << v.size() <<endl;

	// v.insert(v.begin(), 4, 4);

	// cout << "capa: " << v.capacity() <<endl;
	// cout << "size :"  << v.size() <<endl;

	// v.insert(v.begin(), 4);

	// cout << "capa: " << v.capacity() <<endl;
	// cout << "size :"  << v.size() <<endl;
	// // cout << v.capacity() <<endl;

	// int *test = new int[10];
	// for (int i = 0; i < 10 ; ++i)
	// {
	// 	test[i] =i;
	// }
	// for (int i = 0; i < 10 ; ++i)
	// {
	// 	std::cout << test[i];
	// }
	// std::cout << std::endl;
	// int t = 3;
	// std::cout << (*test++ = t) << std::endl;
	// std::cout << *test << std::endl;
	// for (int i = 0; i < 10 ; ++i)
	// {
	// 	std::cout << test[i];
	// }
	// std::cout << std::endl;

	// vector<node>	lst;

	// lst.insert(lst.begin(), NULL);
	// cout << &lst[0] << endl;
	// cout << lst[0].n() << endl;
	// lst.reserve(5);
	// cout << &lst[0] << endl;
	// lst.insert(lst.begin(), NULL);
	// cout << lst[0].n() << endl;
	// lst.insert(lst.begin(), lst.begin(), lst.end());
	// cout << lst[0].n() << endl;

	return 0;
}
