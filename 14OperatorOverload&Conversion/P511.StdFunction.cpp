#include <iostream>
#include <functional>
using namespace std;

void f(int a)
{
    cout << "call void f(int a)" << endl;
}

class TestFunction
{
public:
    void hello(int a)
    {
        cout << "call void TestFunction::hello(int a)" << endl;
    }
    static void func(int a)
    {
        cout << "call static void TestFunction::func(int a)" << endl;
    }
    void operator()(int a)
    {
        cout << "call void TestFunction::operator()(int a)" << endl;
    }
};


// callable object in <functional>
// function
// function pointer
// lambda expression
// object that bind create
// function obejct (object that overload operator())

int main(int argc, char const *argv[])
{
    function<void(int)> funcObj;
    // normal function / function pointer
    funcObj = f;
    f(0);
    funcObj = &f;
    f(0);

    // lambda
    funcObj = [](int a) -> void { cout << "call lambda" <<endl; };
    funcObj(0);

    // static function of class
    funcObj = TestFunction::func;
    funcObj(0);

    // function object
    TestFunction obj;
    funcObj = obj;
    funcObj(0);

    // memeber function of class
    funcObj = std::bind(&TestFunction::hello, &obj, std::placeholders::_1); // still _1, the implicit this do not count to placeholders
    funcObj(0);
    return 0;
}
