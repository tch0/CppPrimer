#include <iostream>
#include <string>
#include <functional>
using namespace std;

class Foo
{
public:
    Foo(const string& s) : str(s) {}
    Foo(string&& s) : str(s) {}
    void print() const
    {
        cout << "void Foo::print(): " << str << endl;
    }
public:
    // a static function that return a pointer to data member
    static string Foo::*data()
    {
        return &Foo::str;
    }
public:
    string str;
};

void callPrint(function<void(const Foo&)> fn, const Foo& foo)
{
    fn(foo);
}

int main(int argc, char const *argv[])
{
    // pointer to data member, like an offset of a specific member in its class
    // point to member of a class, not member of a particular object
    string Foo::*pStr = &Foo::str;
    Foo foo("hello");
    cout << foo.*pStr << endl;
    cout << foo.*Foo::data() << endl;

    // pointer to memeber function
    // it's easy to use auto to define it
    void (Foo::*pnf)() const = &Foo::print; // auto pnf = &Foo::print;
    (foo.*pnf)();
    // using type alias
    using FooPrintFunc = void (Foo::*)() const;
    FooPrintFunc pnf2 = &Foo::print;
    ((&foo)->*pnf2)();

    // treat pointer to member function as callable object
    // use std::function, make implicit parameter this explicit
    function<void(const Foo&)> fn = &Foo::print; // call by object
    function<void(const Foo*)> fn2 = &Foo::print; // call by pointer
    fn(foo);
    fn2(&foo);
    cout << endl;

    // deduce member function type
    // mem_fn : return a function object that forwards to the member function pointer
    callPrint(mem_fn(&Foo::print), foo);
    
    // use std::bind generate function obejct from member function pointer
    callPrint(std::bind(&Foo::print, placeholders::_1), foo);
    cout << endl;

    // like mem_fn, the first paramter could be reference or pointer (call member function by .* or ->*).
    (mem_fn(&Foo::print))(foo);
    (mem_fn(&Foo::print))(&foo);
    (std::bind(&Foo::print, placeholders::_1))(foo);
    (std::bind(&Foo::print, placeholders::_1))(&foo);
    return 0;
}