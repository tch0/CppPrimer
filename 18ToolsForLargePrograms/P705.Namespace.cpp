#include <iostream>
using namespace std;

// using and overload
// name lookup before type check

namespace test
{
    void f(double d)
    {
        cout << "void test::f(double d)" << endl;
    }
}

void f()
{
    cout << "void f()" << endl;
}

void f(int i)
{
    cout << "void f(int i)" << endl;
}

int main(int argc, char const *argv[])
{
    // using declaration will overload function in current domain, and will override the name of outter domain
    {
        using test::f;
        void f(int i); // declaration in this domain, will overload with test::f
        f(10);
        f(10.0);
        // f(); // void f() is overrided by void f(int i) and test::f.
    }
    cout << endl;
    
    // using directive, like add all names in namespace to outter domain, but actually not exact the outter domain, the effect is like add to the global domain
    {
        int f = 10; // override names in global namespace and test::f
        {
            // test::f will overload with global void f() and void f(int i), but name lookup first find int f = 10, so there will be only variable f available
            using namespace test;
            cout << f << endl;
        }
    }
    return 0;
}