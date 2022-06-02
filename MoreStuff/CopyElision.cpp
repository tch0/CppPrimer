#include <iostream>
using namespace std;

// see README.md
// see https://zh.cppreference.com/w/cpp/language/copy_elision
// g++ close copy elision:

class Foo
{
public:
    Foo()
    {
        cout << "Foo()" << endl;
    }
    Foo(const Foo&)
    {
        cout << "Foo(const Foo&)" << endl;
    }
    Foo(Foo&&)
    {
        cout << "Foo(Foo&&)" << endl;
    }
    ~Foo()
    {
        cout << "~Foo()" << endl;
    }
};

// copy elision on constructors
void bar1()
{
    Foo();
}
void bar1_1()
{
    Foo foo = Foo();
}

// RVO: return value optimization
Foo buz()
{
    return Foo();
}
void bar2()
{
    buz();
}
void bar2_1()
{
    Foo foo = buz();
}

// NRVO: named return value optimization
Foo qux()
{
    Foo foo;
    return foo;
}
void bar3()
{
    qux();
}
void bar3_1()
{
    Foo foo = qux();
}
Foo qux2()
{
    Foo foo;
    return std::move(foo);
}
void bar3_2()
{
    Foo foo = qux2();
}

// NRVO closed situation
Foo quxx(bool b)
{
    if (b)
    {
        Foo foo;
        return foo;
    }
    else
    {
        Foo foo;
        return foo;
    }
}
// RVO will always open
Foo quxxx(bool b)
{
    if (b)
    {
        return Foo();
    }
    else
    {
        return Foo();
    }
}
void bar4(bool b)
{
    quxx(b);
}
void bar4_1(bool b)
{
    Foo foo = quxx(b);
}
void bar4_2(bool b)
{
    Foo foo = quxxx(b);
}
// if turn on -fno-elide-constructors, all optimization will be closed.

int main(int argc, char const *argv[])
{
    cout << "test1:" << endl;
    {
        bar1();
    }
    cout << endl;
    {
        bar1_1();
    }
    cout << endl << "test2:" << endl;
    {
        bar2();
    }
    cout << endl;
    {
        bar2_1();
    }
    cout << endl << "test3:" << endl;
    {
        bar3();
    }
    cout << endl;
    {
        bar3_1();
    }
    cout << endl;
    {
        bar3_2(); // no NRVO, so do not use std::move in return value.
    }
    cout << endl << "test4:" << endl;
    {
        bar4(true);
    }
    cout << endl;
    {
        bar4_1(false);
    }
    cout << endl;
    {
        bar4_2(true);
    }
    return 0;
}

