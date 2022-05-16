#include <iostream>
#include <string>
using namespace std;

class BaseClass
{
public:
    static void hello()
    {
        cout << "static void BaseClass::hello()" << endl;
    }
};

class TestClass : public BaseClass
{
public:
    void f();
    static void hello();
};

void TestClass::f()
{
    hello();
}

void TestClass::hello()
{
    cout << "static void TestClas::hello()" << endl;
}

int main(int argc, char const *argv[])
{
    TestClass::hello();
    BaseClass::hello();
    
    TestClass obj;
    BaseClass& r = obj;
    r.hello(); // no dynamic binding for static function, decided in compile time
    return 0;
}
