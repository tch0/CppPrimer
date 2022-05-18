#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <type_traits>
using namespace std;

template<typename T>
void f(const T* a, const T* b)
{
    cout << a << " " << b << endl;
}

template<typename T>
void g(T a, T b)
{
    cout << a << " " << b << endl;
}

template<typename T1, typename T2, typename T3>
T1 sum(T2 a, T3 b)
{
    return a + b;
}

// trailing return type to deduce the return type of function template
// std::remove_reference<decltype(*b)>::type to remove the reference from decltype, obviously it's too long.
template<typename It>
auto sumSeq(It b, It e) -> typename std::remove_reference<decltype(*b)>::type // or std::remove_reference_t<decltype(*b)>
{
    using RetType = typename std::remove_reference_t<decltype(*b)>;
    return accumulate(b, e, 0, plus<RetType>());
}

template<typename T>
int compare(const T& a, const T& b)
{
    if (less<T>()(a, b)) return -1;
    if (less<T>()(b, a)) return 1;
    return 0;
}

int main(int argc, char const *argv[])
{
    int a = 0;
    const int * p = &a;
    int * p2 = &a;
    f(p, p2); // const conversion in template is available

    g("hello", "yes"); // char[] convert to char* automatically

    cout << sum<long long>(1, 2.0) << endl;
    cout << max<double>(1, 2.0) << endl;

    vector<int> vec{1, 2, 3, 4};
    cout << sumSeq(vec.begin(), vec.end()) << endl;

    // deduction from type of function pointer
    int (*pf)(const int&, const int&) = compare;
    cout << pf(1.0, 2.0) << endl;
    return 0;
}
