#include <iostream>
#include <string>
#include <functional>
#include <tuple>
using std::cout;
using std::endl;
using std::string;

class Foo
{
    friend class std::hash<Foo>;
public:
    Foo(int i, const string& s, double d) : iVal(i), str(s), dVal(d) {}
    ~Foo() {}
private:
    int iVal;
    string str;
    double dVal;
};

namespace std
{

// specialize class
template<>
class hash<Foo>
{
public:
    using result_type = size_t;
    using argument_type = Foo;
    size_t operator()(const Foo& foo) const
    {
        return hash<int>()(foo.iVal) ^ hash<string>()(foo.str) ^ hash<double>()(foo.dVal);
    }
};

}

// specialize function ? (the book says that can not do it)
template<typename T1, typename T2>
void f(const T1& a, const T2& b)
{
    cout << a << " " << b << endl;
}

template<typename T2>
void f(const int& a, const T2& b)
{
    cout << "int: " << a << ", " << b << endl;
}

template<typename T2>
void f(const int * const & p, const T2& b)
{
    cout << "int*: " << *p << ", " << b << endl;
}

template<>
void f(const int& a, const string& s)
{
    cout << "int: " << a << ", string: " << s << endl;
}

void f(const int& a, string&& s)
{
    cout << "int: " << a << ", string&&: " << s << endl;
}

// partialy class specialization is valid


template<typename T>
class Bar
{
public:
    Bar(const T& t = T()) : mem(t) {}
    void buz()
    {
        cout << "buz of Bar<T>" << endl;
    }
    void qux()
    {
        cout << "qux of Bar<T>" << endl;
    }
private:
    T mem;
};

// just specialize member function of class instead of the whole class
template<>
void Bar<int>::buz()
{
    cout << "specialized buz of Bar<int>" << endl;
}

int main(int argc, char const *argv[])
{
    cout << sizeof(Foo) << endl;
    cout << std::hash<double>()(10.0) << endl;
    cout << std::hash<Foo>()(Foo(1, "bar", 9.9)) << endl;

    f(10, "foo"); // void f(const int& a, const T2& b)
    f(10.0, "hello"); // call void f(const T1& a, const T2& b)
    int a = 42;
    const int* cp = &a;
    int* p = &a;
    f(cp, "bar"); // call void f(const int * const & p, const T2& b)
    f(p, "bar"); // call void f(const T1& a, const T2& b)

    string s("buz");
    f(10, s); // void f(const int& a, const string& s)
    f(10, string("buz")); // call void f(const int& a, string&& s)

    cout << endl;
    Bar<string> bar;
    bar.buz();
    bar.qux();

    Bar<int> bari;
    bari.buz();
    bari.qux();
    return 0;
}
