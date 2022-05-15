#include <string>
#include <iostream>
#include <utility>
using namespace std;

void f(int && t)
{
    cout << "call void f(int && t)" << endl;
}

// this is redundancy, void f(const int & t) is enough.
void f(const int && t)
{
    cout << "void f(const int && t)" << endl;
}

void f(int & t)
{
    cout << "call void f(int & t)" << endl;
}

void f(const int & t)
{
    cout << "call void f(const int & t)" << endl;
}

class TestClass
{
public:
    string str;
    TestClass(string s) : str(s)
    {
        cout << "call TestClass() of " << str << endl;
    }
    TestClass(const TestClass& obj)
    {
        cout << "call TestClass(const TestClass& obj) of " << str << ", arg is " << obj.str << endl;
    }
    TestClass(TestClass&& obj)
    {
        cout << "call TestClass(TestClass&& obj) of " << str << ", arg is " << obj.str << endl;
    }
    TestClass& operator=(const TestClass& obj)
    {
        cout << "call TestClass& operator=(const TestClass& obj) of " << str << ", arg is " << obj.str << endl;
        return *this;
    }
    TestClass& operator=(TestClass && obj)
    {
        cout << "call TestClass& operator=(TestClass && obj) of " << str << ", arg is " << obj.str << endl;
        return *this;
    }
    ~TestClass()
    {
        cout << "call ~TestClass() of " << str << endl;
    }
};

TestClass f()
{
    return TestClass("tempret");
}

int main(int argc, char const *argv[])
{
    int && t = 3;
    t = 4;
    f(t); // call void f(int & t)

    int & rt = t;
    f(rt); // call void f(int & t)
    rt = 10;
    cout << t << endl;

    const int & crt(rt);
    f(crt); // call void f(const int & t)

    f(3); // call void f(int && t)
    cout << endl;
    
    // test of rvalue reference
    TestClass a("a");
    a = TestClass("temp");
    cout << "Loc 1" << endl;

    TestClass& b = a;
    {
        TestClass&& rrtemp = TestClass("temp2");
        cout << "Loc 2" << endl;
    }
    cout << "Loc 3" << endl;
    TestClass&& rrtemp = TestClass("temp3");

    cout << "Loc 4" << endl;
    TestClass("lhs") = TestClass("rhs");

    cout << "Loc 5" << endl;
    f();
    cout << "Loc end" << endl;
    
    return 0;
}
