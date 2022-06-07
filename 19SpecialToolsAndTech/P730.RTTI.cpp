#include <iostream>
#include <typeinfo>
#include <utility>
using namespace std;

// RTTI: run-time type identification
// key point: typeid operator, dynamic_cast operator

class A
{
public:
    virtual ~A() {};
};
class B : public A {};
class C : public B {};

int main(int argc, char const *argv[])
{
    A* pa = new C;
    if (B* pb = dynamic_cast<B*>(pa))
    {
        cout << "cast pa to B* success" << endl;
    }
    else
    {
        cout << "cast pa to B* failed" << endl;
    }

    // reference
    try
    {
        C& rc = dynamic_cast<C&>(*pa);
        cout << "cast *pa to C& success" << endl;
    }
    catch(const std::bad_cast& e)
    {
        std::cerr << e.what() << '\n';
    }

    // rvalue reference
    try
    {
        B&& rb = dynamic_cast<B&&>(*pa);
        cout << "cast *pa to B&& success" << endl;
    }
    catch(const std::bad_cast& e)
    {
        std::cerr << e.what() << '\n';
    }

    delete pa;
    pa = new B();
    try
    {
        C& rc = dynamic_cast<C&>(*pa);
        cout << "cast *pa to C& success" << endl;
    }
    catch(const std::bad_cast& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}
