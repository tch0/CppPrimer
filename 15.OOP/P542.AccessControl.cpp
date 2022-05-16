#include <iostream>
using namespace std;

class Base
{
public:
    virtual void bar()
    {
        foo();
    }
protected:
    virtual void foo()
    {
        cout << "void Base::foo()" << endl;
    }
};

class Derived : public Base
{
private:
    void foo() override
    {
        Base::foo();
        cout << "void Derived::foo()" << endl;
    }
};

int main(int argc, char const *argv[])
{
    Derived d;
    Base& b = d;
    b.bar();
    return 0;
}
