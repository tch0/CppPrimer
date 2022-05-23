#include <iostream>
#include <tuple>
#include <string>
using std::string;
using std::ostream;
using std::cout;
using std::endl;


// print a single tuple element
template<typename T>
void printElement(ostream& os, const T& t)
{
    os << t;
}
template<>
void printElement(ostream& os, const string& t)
{
    os << '"' << t << '"';
}

// solution 1: class template recursion
/*
template<typename Tuple, size_t N>
struct tuple_print
{
    static void print(const Tuple& t, std::ostream& os)
    {
        tuple_print<Tuple, N-1>::print(t, os);
        os << ", " << std::get<N-1>(t);
    }
};
template<typename Tuple>
struct tuple_print<Tuple, 1>
{
    static void print(const Tuple& t, std::ostream& os)
    {
        os << std::get<0>(t);
    }
};
*/

// solution 2: wrap size_t, function template recursion and overloading
template<size_t> struct uint{}; // wrap size_t
template<typename Tuple, size_t N>
void print(ostream& os, const Tuple& t, uint<N>)
{
    print(os, t, uint<N-1>());
    os << ", ";
    printElement(os, std::get<N-1>(t));
}
template<typename Tuple>
void print(ostream& os, const Tuple& t, uint<1>)
{
    printElement(os, std::get<0>(t));
}

template<typename... Args>
ostream& operator<<(ostream& os, const std::tuple<Args...>& t)
{
    os << "(";
    print(os, t, uint<sizeof...(Args)>());
    os << ")";
    return os;
}

int main(int argc, char const *argv[])
{
    std::tuple<int, double, string> t(1, 2.2, "foo");
    cout << t << endl;

    cout << std::tuple_size<decltype(t)>::value << endl;
    std::tuple_element<1, decltype(t)>::type d = 10.9;
    cout << d << endl;

    std::tuple<int, double, const char*> t2(1, 2.2, "bar");
    cout << (t == t2) << endl;
    cout << (t > t2) << endl;
    return 0;
}