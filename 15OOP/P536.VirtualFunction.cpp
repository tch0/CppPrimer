#include <iostream>
using namespace std;

class BaseClass
{
public:
    void hello() const
    {
        cout << "void BaseClass::hello() const" << endl;
    }
    virtual void run() const
    {
        cout << "void BaseClass::run() const" << endl;
    }
};

class TestClass : public BaseClass
{
public:
    void hello() const
    {
        cout << "void TestClass::hello() const" << endl;
    }
    void run() const override final;
};

void TestClass::run() const
{
    cout << "void TestClass::run() const override" << endl;
}

int main(int argc, char const *argv[])
{
    TestClass obj;
    BaseClass& b = obj;
    b.run();
    b.BaseClass::run();
    b.hello();
    return 0;
}
