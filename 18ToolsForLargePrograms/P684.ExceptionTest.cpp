#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class MyException
{
public:
    MyException(const string& s) : str(s)
    {
        cout << "MyException constructed : " << str << "(" << this << ")" << endl;
    }
    ~MyException()
    {
        cout << "MyException destructed : " << str << ", address: " << this << endl;
    }
    MyException(const MyException& e) : str("copy of " + e.str)
    {
        cout << "copying MyException, " << "source: " << e.str << "(" << &e << "), " << "target: " << str << "(" << this << ")" << endl;
    }
private:
    string str;
};

void sameExceptionTest()
{
    try
    {
        MyException e("temp");
        cout << "\tthe address of thrown exception e: " << &e << endl;
        throw e; // copying object e
    }
    catch (MyException e)
    {
        cout << "\tthe address of caught exception e: " << &e << endl; // not a same exception, execute a copy initilization in throw expression
    }
}

// samiliar return value test
MyException returnValueTest1(bool b)
{
    if (b)
    {
        MyException e("local-true1");
        return e;
    }
    else
    {
        MyException e("local-false1");
        return e;
    }
}

class Foo
{
public:
    Foo(const string& s) : str(s)
    {
        cout << "Foo constructed : " << str << "(" << this << ")" << endl;
    }
    ~Foo()
    {
        cout << "Foo destructed : " << str << ", address: " << this << endl;
    }
    Foo(const Foo& e) : str("copy of " + e.str)
    {
        cout << "copying Foo, " << "source: " << e.str << "(" << &e << "), " << "target: " << str << "(" << this << ")" << endl;
    }
    Foo(Foo&& e) : str("moving of " + e.str)
    {
        cout << "moving Foo, " << "source: " << e.str << "(" << &e << "), " << "target: " << str << "(" << this << ")" << endl;
    }
private:
    string str;
};

Foo returnValueTest2(bool b)
{
    if (b)
    {
        return Foo("ret-true2");
    }
    else
    {
        return Foo("ret-false2");
    }
}

Foo returnValueTest3(bool b)
{
    if (b)
    {
        Foo foo("ret-true3");
        return foo;
    }
    else
    {
        Foo foo("ret-false3");
        return foo;
    }
}

/*
1. 左值是有地址的变量，具有持久性，并且可以更改。即使左值是常量，也可以通过const_static或者构造指针来更改。

2. 右值是没有地址的常量，没有任何办法去更改右值的值，并且右值在使用后就被立即销毁。
*/

Foo returnValueTest4()
{
    Foo foo("local-temp");
    cout << "address of temp var foo: " << &foo << endl;
    return foo;
}

// no destructor and copy-constructor: there will be no optimization
class Bar
{
public:
    Bar()
    {
        cout << "Bar constructed" << endl;
    }
};

Bar returnValueTest5()
{
    Bar bar;
    cout << "address of temp var bar: " << &bar << endl;
    return bar;
}

// use rvalue reference to receive function return value
Foo returnValueTest6()
{
    Foo foo("local-test6");
    cout << "address of temp var foo: " << &foo << endl;
    return foo;
}

int main(int argc, char const *argv[])
{
    sameExceptionTest();
    cout << endl;
    {
        MyException e = returnValueTest1(false);
    }
    cout << endl;
    {
        Foo e = returnValueTest2(false);
    }
    cout << endl;
    {
        returnValueTest3(false);
    }
    cout << endl;
    {
        Foo foo = returnValueTest3(true);
    }
    cout << endl;
    {
        Foo foo = returnValueTest4();
        cout << "address of new var foo: " << &foo << endl;
    }
    cout << endl;
    {
        Bar bar = returnValueTest5();
        cout << "address of new var bar: " << &bar << endl; // not same address with the temp var bar
    }
    cout << endl;
    {
        Foo&& foo = returnValueTest6();
        cout << "address of rvalue reference foo: " << &foo << endl;
    }
    cout << endl;
    // rvalue test, extend the life time of a rvalue(precisely xvalue)
    {
        Foo&& foo = Foo("rvalue-test");
        cout << "Loc" << endl;
    }
    cout << "end" << endl;

    return 0;
}
