#include <iostream>
#include <typeinfo>
#include <vector>
#include <utility>
using namespace std;

// typeid operator
// form: typeid(e), e can be a name of type or an expression
// result type is struct type_info: in <typeinfo>

class A
{
public:
    virtual ~A() {}
};

class B : public A {};


// example that use RTTI: judge equal for dirived classes
class Base
{
    friend bool operator==(const Base&, const Base&);
public:
    Base(string a, int b, double c) : s(a), i(b), d(c) {}
protected:
    virtual bool equal(const Base&) const;
private:
    string s;
    int i;
    double d;
};

class Derived : public Base
{
public:
    Derived(string a, int b, double c, const vector<int>& v1, const vector<string>& v2) : 
        Base(a, b, c), veci(v1), vecs(v2) {}
protected:
    bool equal(const Base&) const;
private:
    vector<int> veci;
    vector<string> vecs;
};

bool operator==(const Base& lhs, const Base& rhs)
{
    return typeid(lhs) == typeid(rhs) && lhs.equal(rhs);
}

bool Base::equal(const Base& rhs) const
{
    return s == rhs.s && i == rhs.i && d == rhs.d;
}

bool Derived::equal(const Base& rhs) const
{
    auto r = dynamic_cast<const Derived&>(rhs);
    return veci == r.veci && vecs == r.vecs;
}

int main(int argc, char const *argv[])
{
    B* pb = new B();
    A* pa = pb;
    // polymorphic type, evaluate at run-time
    if (typeid(*pa) == typeid(*pb))
    {
        cout << "*pa and *pb are same type" << endl;
    }
    else
    {
        cout << "*pa and *pb are not same type" << endl;
    }

    // pointer, evaluate at compile-time
    if (typeid(pa) != typeid(pb))
    {
        cout << "pa and pb are not a same pointer type" << endl;
    }

    // RTTI example test
    Derived d1("hello", 10, 1.0, {1, 2, 3}, {"yes", "no"});
    Base b1("hello", 10, 1.0);
    cout << boolalpha << (d1 == b1) << endl;
    Base b2("hello", 10, 1.0);
    cout << (b1 == b2) << endl;
    Derived d2("hello", 10, 1.0, {1, 2, 3}, {"yes", "no"});
    cout << (d1 == d2) << endl;

    cout << typeid(d1).name() << endl;
    cout << typeid(*(static_cast<Base*>(&d1))).name() << endl;

    // type_info::name test: decorated name of type?
    cout << endl;
    cout << typeid(int).name() << endl;
    cout << typeid(double).name() << endl;
    cout << typeid(int[]).name() << endl;
    cout << typeid(int(*)(double, int)).name() << endl;
    cout << typeid(int(&)(double, int)).name() << endl;
    cout << typeid(vector<int>).name() << endl;
    cout << typeid(const int*).name() << endl;
    return 0;
}
