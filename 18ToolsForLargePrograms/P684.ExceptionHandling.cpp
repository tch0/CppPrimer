#include <iostream>
#include <string>
#include <exception> // exception
#include <vector>
#include <typeinfo> // bad_cast
#include <new> // bad_alloc
#include <stdexcept> // runtime_error, logic_error
using namespace std;

// function try block, take care of exception thrown from constructor initializer-list
class Foo
{
private:
    string str;
    int i;
public:
    // function try block
    Foo(const string& s, int a) try : str(s), i(a) {
        throw exception();
    } catch (exception& e)
    {
        cout << "exception while constructing a Foo object: " << e.what() << endl;
    }
};


// noexcept specification: after const &/&&, before final/override/=0.
// the argument must can convert to bool.
// forward compatible : throw() equals to noexcept
void bar() noexcept
{
    
}

void bar(int i)
{
    
}

// may throw an exception or noexcept depends on the funtions it calls.
// noexcept expression/operator : return a bool value.
void buz() noexcept(noexcept(bar()) && noexcept(bar(0)))
{
    bar();
    bar(1);
    cout << "void buz() noexcept(noexcept(bar()) && noexcept(bar(0)))" << endl;
}

// warning here.
void qux() noexcept
{
    throw exception();
}


int main(int argc, char const *argv[])
{
    // destructor should not throw an exception out of it's body.
    // objects will destruct while stack unwinding.
    try
    {
        static std::exception e;
        throw &e;
    }
    catch(const std::exception* pe)
    {
        std::cerr << pe->what() << '\n';
    }

    // everything can be thrown out, even an array or pointer, but usually an exception.
    try
    {
        throw vector<int>(3, 0);
    }
    catch(vector<int>& vec)
    {
        for (auto elem : vec)
        {
            cout << elem << " ";
        }
        cout << endl;
    }

    // function trye block
    // Foo("foo", 0); // will terminate

    // noexcept specification / noexcept expression/operator
    cout << boolalpha << noexcept(bar) << endl; // true, bar means the no-paramter one
    cout << noexcept(bar(0)) << endl;
    cout << noexcept(buz()) << endl; // false

    void (*pf)();
    pf = bar;
    pf = buz;

    void (*pnf)() noexcept;
    pnf = bar;
    pnf = buz; // invalid theoretically, but gcc do not report an error.
    pnf();

    // calling a noexcept funtion but throwing an exception inside, will call terminate().
    qux();
    return 0;
}
