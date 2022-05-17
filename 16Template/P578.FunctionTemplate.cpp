#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

template<typename T>
int compare(const T& v1, const T& v2)
{
    if (less<T>()(v1, v2)) return 1;
    if (less<T>()(v2, v1)) return -1;
    return 0;
}

// non-type parameter
template<size_t N, size_t M>
int compare(const char (&p1)[N], const char (&p2)[M])
{
    return strcmp(p1, p2);
}

// constexpr and inline specifier
template<typename T, size_t N>
constexpr inline size_t arraySize(const T (&arr)[N])
{
    return N;
}

int main(int argc, char const *argv[])
{
    cout << compare(1.0, 2.0) << endl;
    cout << compare<6, 6>("hello", "world") << endl;
    cout << compare(vector<int>{1, 2}, vector<int>{1, 2}) << endl;
    int A[10];
    cout << arraySize(A) << endl;
    return 0;
}
