#include <iostream>
#include <stdexcept>
using namespace std;

class SmallInt
{
public:
    SmallInt(int i = 0) : val(i)
    {
        if (i < 0 || i > 255)
        {
            throw std::out_of_range("Bad SmallInt value");
        }
    }
    operator int()
    {
        return val;
    }
    operator bool()
    {
        return val != 0;
    }
private:
    int val;
};

void f(SmallInt a)
{
    cout << "call void f(SmallInt a)" << endl;
}

void f(int a)
{
    cout << "void f(int a)" << endl;
}

void f(bool a)
{
    cout << "void f(bool a)" << endl;
}

int main(int argc, char const *argv[])
{
    f(SmallInt(10));
    f(10);
    f(true);
    return 0;
}
