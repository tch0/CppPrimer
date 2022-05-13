#include <string>
#include <iostream>
using namespace std;

class TestClass
{
public:
    TestClass(int a) : val(a)
    {
        cout << "call TestClass(int)" << endl;
    }
    explicit TestClass(const TestClass& obj) : val(obj.val) // usually copy constructor should not be explicit
    {
        cout << "call expiclit TestClass(const TestClass& obj)" << endl;
    }
private:
    int val;
};

void testParameter(TestClass obj)
{
}

TestClass testReturnValue()
{
    // return TestClass(10); // invalid, because explicit
    return 10; // valid, because converting constructor
}

int main(int argc, char const *argv[])
{
    TestClass obj0(1); // always valid
    TestClass obj = 10; // if copy contructor is private, this statement will be invalid
    TestClass obj2(obj);
    testParameter(10);
    // testParameter(obj); // invaild
    testReturnValue();

    obj = obj2; // using synthesized copy assignment operator
    return 0;
}
