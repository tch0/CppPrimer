#include <iostream>
#include <type_traits>
using namespace std;

// lvalue, rvalue
// xvalue and prvalue
// lvalue reference, rvalue reference
// as return type and passing to function

class MyString
{
    friend ostream& operator<<(ostream& os, const MyString& s);
public:
    MyString() : str(new string())
    {
    }
    MyString(const string& s) : str(new string(s))
    {
        cout << "MyString(const string& s) : str(s)" << endl;
    }
    MyString(const MyString& s) : str(new string(*s.str))
    {
        cout << "MyString(const MyString& s)" << endl;
    }
    MyString(MyString&& s) : str(s.str)
    {
        s.str = nullptr;
        cout << "MyString(MyString&& s)" << endl;
    }
    MyString& operator=(const MyString& s)
    {
        cout << "MyString& operator=(const MyString& s)" << endl;
        string* old = str;
        str = new string(*s.str);
        delete old;
        return *this;
    }
    MyString& operator=(MyString&& s)
    {
        cout << "MyString& operator=(MyString&& s)" << endl;
        // deal with self-assignment
        if (&s == this)
        {
            return *this;
        }
        if (str)
        {
            delete str;
            str = nullptr;
        }
        str = s.str;
        s.str = nullptr;
        return *this;
    }
    ~MyString()
    {
        cout << "~MyString()" << endl;
        delete str;
        str = nullptr;
    }
    void hello() &
    {
        cout << "void hello() &" << endl;
    }
    void hello() &&
    {
        cout << "void hello() &&" << endl;
    }
private:
    string* str;
};

ostream& operator<<(ostream& os, const MyString& s)
{
    if (s.str)
    {
        os << *s.str;
    }
    else
    {
        os << "nullptr";
    }
    return os;
}

class Foo
{
public:
    Foo(const string& s) : str(s)
    {
        cout << "Foo()" << endl;
    }
    Foo(const Foo& foo) : str(foo.str)
    {
        cout << "Foo(const Foo& foo)" << endl;
    }
    Foo(Foo&& foo) : str(std::move(foo.str))
    {
        cout << "Foo(Foo&& foo)" << endl;
    }
    ~Foo()
    {
        cout << "~Foo()" << endl;
    }
    void test()
    {
        cout << str << endl;
    }

    MyString str;
};

Foo bar(bool b)
{
    if (b)
    {
        Foo foo("true");
        return foo;
    }
    else
    {
        Foo foo("false");
        return foo;
    }
}

int main(int argc, char const *argv[])
{
    {
        Foo&& foo = std::move(Foo("hello"));
        cout << "Loc" << endl;
        cout << &foo << endl;
        foo.test();
    }
    cout << endl;

    {
        MyString s("test");
        s = Foo("yes").str; // memeber of rvalue is a rvalue
    }
    
    cout << endl;
    
    {
        MyString A[10] = {};
        MyString s;
        s = std::move(A)[0]; // [] of a xvalue is lvalue? they said [] of a rvalue array should be a rvalue.
    }
    cout << "end" << endl;
    return 0;
}