#ifndef MAP_HPP
#define MAP_HPP

#include "utils.hpp"
#include <memory>
namespace ft
{
template <	typename Key,
			typename T,
			typename Compare = ft::less<Key>,
			typename Alloc = std::allocator<ft::pair<const Key,T> >
			>
class map
{
public:
	typedef	Key															key_type;
	typedef	T															mapped_type;
	typedef	ft::pair<const Key, T>										value_type;
	typedef	size_t														size_type;
	typedef	ptrdiff_t													difference_type;
	typedef	Compare														key_compare;
	typedef	Alloc														allocator_type
	typedef	typename allocator_type::reference							reference;
	typedef	typename allocator_type::const_reference					const_reference;
	typedef	typename allocator_type::pointer							pointer;
	typedef	typename allocator_type::const_pointer						const_pointer;
	typedef	ft::red_black_tree<value_type, key_compare>::iterator		iterator
	typedef	ft::red_black_tree<value_type, key_compare>::const_iterator	const_iterator
	typedef	ft::reverse_iterator<iterator>								reverse_iterator
	typedef	ft::reverse_iterator<const_iterator>						const_reverse_iterator

	class value_compare: public ft::binary_function<value_type, value_type, bool>
	{
		friend class map<key_type, mapped_type, key_compare, Alloc>;
	protected:
		Compare	comp;
		value_compare (Compare c) : comp(c) {}
	public:
		bool operator() (const value_type& x, const value_type& y) const
		{
			return comp(x.first, y.first);
		}
	};

	explicit map (const key_compare& comp = key_compare(),
	const allocator_type& alloc = allocator_type())
	:
		_comp(comp),
		_alloc(alloc),
		_tree()
	{}

template <class InputIterator>
	map (InputIterator first, InputIterator last,
	const key_compare& comp = key_compare(),
	const allocator_type& alloc = allocator_type(),
	ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = my_nullptr)
	:
		_comp(comp),
		_alloc(alloc),
		_tree()
	{
		this->insert(first, last);
	}
	map (const map& x)
	:
		_comp(x.comp),
		_alloc(x.alloc),
		_tree()
	{
		this->insert(x.begin(), x.end());
	}
	~map ()
	{
		this->clear();
	}
	map& operator= (const map& x)
	{
		if (this == &x)
			return (*this);
		this->clear();
		this->insert(x.begin(), x.end());
		return (*this);
	}


// Iterators:
// begin
// Return iterator to beginning (public member function )
// end
// Return iterator to end (public member function )
// rbegin
// Return reverse iterator to reverse beginning (public member function )
// rend
// Return reverse iterator to reverse end (public member function )

// Capacity:
	bool empty() const { return (this->_tree.empty()); }
	size_type size() const ( return (this->_tree.size()); )
	size_type max_size() const { return (_tree.max_size()); }


// Element access:
// operator[]
// Access element (public member function )

// Modifiers:
// insert
// Insert elements (public member function )
	pair<iterator,bool> insert (const value_type& val)
	{

	}
	iterator insert (iterator position, const value_type& val);
template <class InputIterator>
	void insert (InputIterator first, InputIterator last);
// erase
// Erase elements (public member function )
// swap
// Swap content (public member function )
// clear
// Clear content (public member function )

// Observers:
// key_comp
// Return key comparison object (public member function )
// value_comp
// Return value comparison object (public member function )

// Operations:
	iterator							find (const key_type& k) { return (_tree.find(k)); }
	const_iterator						find (const key_type& k) const { return (_tree.find(k)); }
	size_type							count (const key_type& k) const;
	iterator							lower_bound (const key_type& k)
	{
		iterator	it1 = this->begin();
		iterator	it2 = this->end();
		while (it1 != it2)
		{
			if (_comp(it1->first, k) == false)
				break;
			++it1;
		}
		return (it1);
	}
	iterator							upper_bound (const key_type& k)
	{
		iterator	it1 = this->begin();
		iterator	it2 = this->end();
		while (it1 != it2)
		{
			if (_comp(k, it1->first) == true)
				break;
			++it1;
		}
		return (it1);
	}
	const_iterator						lower_bound (const key_type& k) const
	{ return (const_iterator(lower_bound(k))); }
	const_iterator						upper_bound (const key_type& k) const
	{ return (const_iterator(upper_bound(k))); }
	pair<const_iterator,const_iterator>	equal_range (const key_type& k) const
	{ return (ft::make_pair(this->lower_bound(k), this->upper_bound(k))); }
	pair<iterator,iterator>				equal_range (const key_type& k)
	{ return (ft::make_pair(this->lower_bound(k), this->upper_bound(k))); }
	allocator_type 						get_allocator() const
	{ return (allocator_type()); }


private:
	key_compare								_comp;
	allocator_type							_alloc;
	red_black_tree<value_type, key_compare>	_tree;


};

}

#endif
