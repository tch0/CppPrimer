#include <iostream>
using namespace std;

class A
{
public:
    A()
    {
        cout << "A()" << endl;
    }
    A(int)
    {
        cout << "A(int)" << endl;
    }
    ~A()
    {
        cout << "~A()" << endl;
    }
};

class B : virtual public A
{
public:
    B() : A(1)
    {
        cout << "B()" << endl;
    }
    ~B()
    {
        cout << "~B()" << endl;
    }
};

class C : virtual public A
{
public:
    C() : A(1)
    {
        cout << "C()" << endl;
    }
    ~C()
    {
        cout << "~C()" << endl;
    }
};

class D
{
public:
    D()
    {
        cout << "D()" << endl;
    }
    ~D()
    {
        cout << "~D()" << endl;
    }
};

class E : virtual public D, public B, public C
{
public:
    E()
    {
        cout << "E()" << endl;
    }
    ~E()
    {
        cout << "~E()" << endl;
    }
};

int main(int argc, char const *argv[])
{
    E();
    return 0;
}
