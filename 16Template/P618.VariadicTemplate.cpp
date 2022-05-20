#include <iostream>
#include <string>
#include <vector>
using namespace std;

template<typename ... Args> 
void f(Args ... args)
{
    cout << sizeof...(Args) << endl;
    cout << sizeof...(args) << endl;
}

// variadic template function are usually recursive
template<typename T>
ostream& print(ostream& os, const T& t)
{
    return os << t;
}

template<typename T, typename... Args>
ostream& print(ostream& os, const T& t, const Args&... args)
{
    os << t << " ";
    return print(os, args...);
}

int main(int argc, char const *argv[])
{
    f("hello", 10, 1.0, string(""));

    print(cout, "foo", 10, 9.9, string("bar"));
    return 0;
}
