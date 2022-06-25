#include <iostream>
using namespace std;

// steps of overload resolution:
// 1. find all candidate functions
// 2. find all viable functions
// 3. find best matching function (non or multiple ambiguous result will cause an error)

void f()
{
    cout << "f 0" << endl;
}

void f(int a)
{
    cout << "f 1" << endl;
}

void f(int a, int b)
{
    cout << "f 2" << endl;
}

void f(double a, double b = 3.0)
{
    cout << "f 3" << endl;
}

// const conversion
void g(const int * const & p)
{
    cout << "g 1" << endl;
}
void g(const int *& p)
{
    cout << "g 2" << endl;
}
void g(int *& p)
{
    cout << "g 3" << endl;
}

// different level of const conversion
void h(const int * const * const * ppp)
{
    cout << "h 1" << endl;
}
void h(int * const * const * ppp)
{
    cout << "h 2" << endl;
}
void h(int ** const * ppp)
{
    cout << "h 3" << endl;
}

int main(int argc, char const *argv[])
{
    f(1.0); // will call f 3
    // f(42, 1.0); // call of overloaded 'f(int, double)' is ambiguous
    
    const int * p = nullptr;
    g(p); // g 2
    const int * const p1 = nullptr;
    g(p1); // g 1
    int * p2 = nullptr;
    g(p2); // g 3
    int * const p3 = nullptr;
    g(p3); // g 1

    int *** ppp = nullptr;
    const int * const * const * ppp1 = ppp;
    int * const * const * ppp2 = ppp;
    int ** const * ppp3 = ppp;
    // const int ** const * pp4 = &pp; // invalid
    // const int *** ppp4 = &pp; // invalid
    // const must be added from back to front, if front is added, then must add all const behind it.

    int * const *** pppp = nullptr;
    int * const ** const * pppp1 = pppp;
    const int * const * const * const * pppp2 = pppp;

    // final test
    int *** pppx = nullptr;
    h(pppx); // h 3
    return 0;
}