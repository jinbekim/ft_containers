#ifndef ENABLE_IF
#define ENABLE_IF

namespace ft
{
/* enable_if */
template <bool cond, typename T = void> struct enable_if {};
template <typename T> struct enable_if <true, T> { typedef T type; };
}

#endif
