#include "iterator.hpp"

/* utils.hpp */

namespace ft
{

template < typename InputIt >
typename ft::iterator_traits<InputIt>::diffrence_type	distance(InputIt first, InputIt last)
{
	typename ft::iterator_traits<InputIt>::diffrence_type	dist = 0;
	while (first != last){
		++first;
		++dist;
	}
	return dist;
}

}
