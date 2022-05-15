#include <iostream>
using namespace std;

class TestClass
{
    friend ostream& operator<<(ostream& os, const TestClass& obj);
private:
    int val;
public:
    TestClass(int v = 0) : val(v) {}
    ~TestClass() {}
    // pre ++ and --
    TestClass& operator++()
    {
        ++val;
        return *this;
    }
    TestClass& operator--()
    {
        --val;
        return *this;
    }
    // post ++ and --
    TestClass operator++(int)
    {
        ++val;
        return TestClass(val - 1);
    }
    TestClass operator--(int)
    {
        --val;
        return TestClass(val + 1);
    }
};

ostream& operator<<(ostream& os, const TestClass& obj)
{
    os << "TestClass: " << obj.val;
    return os;
}

int main(int argc, char const *argv[])
{
    TestClass a(10);
    cout << a << endl;
    cout << ++a << endl;
    cout << a++ << endl;
    cout << a << endl;
    cout << --a << endl;
    cout << a-- << endl;
    cout << a << endl;
    // pre version
    a.operator++();
    // post version
    a.operator++(0);
    cout << a << endl;
    return 0;
}
