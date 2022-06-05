#include <iostream>
#include <new>
using namespace std;

class Foo
{
public:
    Foo()
    {
        cout << "Foo()" << endl;
    }
    ~Foo()
    {
        cout << "~Foo()" << endl;
    }
};

int main(int argc, char const *argv[])
{
    Foo* foo = static_cast<Foo*>(operator new(sizeof(Foo)));
    // placement new, only call constructor
    new (foo) Foo();
    // call destrcutor directly
    foo->~Foo();

    // the address of placement new does not need from operator new, also can be stack memory, placement new only construct the object
    // just for test.
    Foo foo2;
    new (&foo2) Foo();
    foo2.~Foo();
    return 0;
}
