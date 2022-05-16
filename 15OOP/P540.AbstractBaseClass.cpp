#include <iostream>
using namespace std;

class Base
{
public:
    virtual void foo() = 0;
};

void Base::foo()
{
    cout << "void Base::foo()" << endl;
}

class Derived : public Base
{
public:
    void foo() override
    {
        cout << "void Derived::foo()" << endl;
    }
};


int main(int argc, char const *argv[])
{
    Derived d;
    Base& b = d;
    b.foo();
    return 0;
}
