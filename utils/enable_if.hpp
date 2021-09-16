#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP

namespace ft
{

/* enable_if */
template <bool cond, typename T = void> struct enable_if {};
template <typename T> struct enable_if <true, T> { typedef T type; };

}

#endif
