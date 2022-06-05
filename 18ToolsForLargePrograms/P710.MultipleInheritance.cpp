#include <iostream>
using namespace std;

class A
{
public:
    A()
    {
        cout << "A()" << endl;
    }
    void print()
    {
        cout << "from A" << endl;
    }
};

class B : public A
{
public:
    B()
    {
        cout << "B()" << endl;
    }
    void print()
    {
        cout << "from B" << endl;
    }
};

class C : public A
{
public:
    C()
    {
        cout << "C()" << endl;
    }
    void print()
    {
        cout << "from C" << endl;
    }
};

class D : public B, public C
{
public:
    D()
    {
        cout << "D()" << endl;
    }
    void print()
    {
        cout << "from D" << endl;
        C::print();
    }
};


int main(int argc, char const *argv[])
{
    D().print();
    return 0;
}
