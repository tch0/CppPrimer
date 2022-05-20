#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <type_traits>
#include <utility> // for std::forward

using std::cout;
using std::endl;

// the implementation of std::move
template<typename T>
typename std::remove_reference<T>::type&& move(T&& t)
{
    return static_cast<typename std::remove_reference<T>::type&&>(t);
}
// we can static_cast a l-value to r-value reference.

template<typename F, typename T1, typename T2>
void flip1(F f, T1&& t1, T2&& t2) // rvalue reference to save const and reference traits
{
    f(t2, t1); // flip the arguments
}

// dispatch arguments with traits to other function : std::forward
// std::forward<T> return T&&, keep const and reference traits through reference folding.
// int& &&/int&& & --> int&
// int&& && --> int&&
template<typename F, typename T1, typename T2>
void flip2(F f, T1&& t1, T2&& t2) // rvalue reference to save const and reference traits
{
    f(std::forward<T2>(t2), std::forward<T1>(t1)); // flip the arguments
}

void g(int&& i, int& j)
{
    cout << i << " " << j << endl;
}

int main(int argc, char const *argv[])
{
    int i = 0;
    // flip1(g, i, 42); // T1 will be int&, T2 will be int&&, in filp1, int&& t1 can not bind to paramter int&& i in function g.
    // because r-value reference itself is a variable which is a l-value.

    flip2(g, i, 42);
    int j = 42;
    flip2(g, i, std::move(j));
    return 0;
}
