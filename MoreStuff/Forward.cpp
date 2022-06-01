#include <iostream>
#include <type_traits>
using namespace std;

// implementation of std::forward

// forward lvalue
template<typename T>
constexpr T&& myForward(typename remove_reference<T>::type& arg) noexcept 
{
    return static_cast<T&&>(arg);
}

// forward rvalue
template<typename T>
constexpr T&& myForward(typename remove_reference<T>::type&& arg) noexcept
{
    static_assert(!is_lvalue_reference<T>::value, "bad forward call");
    return static_cast<T&&>(arg);
}

template<typename T1, typename T2>
T1&& staticCastFunc(T1&& t1, T2&& t2)
{
    return static_cast<T1&&>(t2);
}

template<typename T1, typename T2>
T1&& forwardCastFunc(T1&& t1, T2&& t2)
{
    return myForward<T1>(t2);
}

struct TypeB {};
struct TypeA
{
public:
    TypeA() { cout << "TypeA()" << endl; }
    TypeA(const TypeA&) { cout << "TypeA(const TypeA&)" << endl; }
    ~TypeA() { cout << "~TypeA()" << endl; }
    TypeA(const TypeB&) { cout << "TypeA(const TypeB&)" << endl; }
};

void forwardTypeCastTest(const TypeA& a, const TypeB& b)
{
    cout << "staticCastFunc:" << endl;
    staticCastFunc(a, b);
    cout << "forwardCastFunc:" << endl;
    forwardCastFunc(a, b);
}

int main(int argc, char const *argv[])
{
    TypeA t1;
    TypeB t2;
    forwardTypeCastTest(t1, t2);
    return 0;
}
