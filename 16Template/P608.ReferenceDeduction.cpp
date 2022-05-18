#include <iostream>
#include <functional>
#include <algorithm>
#include <type_traits>
using namespace std;

// template<typename T>
// void f(T& r)
// {
//     cout << "void f(T& r): ";
//     cout << r << endl;
// }

template<typename T>
void f(T&& r)
{
    cout << "void f(T&& r): ";
    cout << r << endl;
}

int main(int argc, char const *argv[])
{
    f(10);
    const int a = 10;
    f(a); // T will be const int&
    f(string("hello")); // r-value bind to T&& version
    int b = 0;
    f(b); // actually the parameter will fold to void f(T& r)
    return 0;
}
