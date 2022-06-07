#include <iostream>
using namespace std;

// nested class

class Foo
{
public:
    class Bar
    {
    public:
        Bar(const Foo& foo) : str(foo.str)
        {
        }
        void print()
        {
            cout << str << endl;
        }
    private:
        string str;
    };
public:
    Foo(const string& s) : str(s) {}
private:
    string str;
};

int main(int argc, char const *argv[])
{
    Foo foo("hello");
    Foo::Bar bar(foo);
    bar.print();
    return 0;
}