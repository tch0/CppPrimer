#include <string>
#include <iostream>
#include <algorithm>
#include <utility>
using namespace std;

class MyString
{
public:
    string str;
public:
    MyString(const char* s) : str(s) {}
    MyString(const string& s = "") : str(s) {}
    MyString(const MyString& s) : str(s.str)
    {
        cout << "call -- MyString(const MyString& s)" << endl;
    }
    MyString(MyString&& s) : str(std::move(s.str))
    {
        cout << "call -- MyString(MyString&& s)" << endl;
    }
    MyString& operator=(const MyString& rhs) & // prevent assignment to a rvalue
    {
        cout << "call MyString& operator=(const MyString& rhs) &" << endl;
        str = rhs.str;
        return *this;
    }
    MyString& operator=(MyString&& rhs) & // prevent assignment to a rvalue
    {
        cout << "call MyString& operator=(MyString&& rhs) &" << endl;
        str = std::move(rhs.str);
        return *this;
    }
    MyString& operator=(const MyString& rhs) && // only for changable rvalue
    {
        cout << "call MyString& operator=(const MyString& rhs) &&" << endl;
        str = rhs.str;
        return *this;
    }
    MyString& operator=(MyString&& rhs) && // only for changable rvalue
    {
        cout << "call MyString& operator=(MyString&& rhs) &&" << endl;
        str = std::move(rhs.str);
        return *this;
    }
    MyString operator+(const MyString& rhs) const
    {
        return MyString(str + rhs.str);
    }

    MyString sorted() && // for changable rvalue
    {
        cout << "call MyString sorted() &&" << endl;
        sort(str.begin(), str.end());
        return *this; // will call MyString(MyString&& s)
    }
    MyString sorted() const &
    {
        cout << "call MyString sorted() const &" << endl;
        MyString ret(*this); // will call MyString(const MyString& s)
        sort(ret.str.begin(), ret.str.end());
        return std::move(ret); // will call MyString(MyString&& s)
    }
};

int main(int argc, char const *argv[])
{
    string s1, s2;
    // assign to a rvalue
    s1 + s2 = "hello";
    string("hello") = "world";

    MyString ms1, ms2;
    ms1 + ms2 = "hello"; // call MyString& operator=(MyString&& rhs) &&
    ms1 + ms2 = ms1;     // call MyString& operator=(const MyString& rhs) &&
    ms1 = ms1 + ms2;     // call MyString& operator=(MyString&& rhs) &
    ms1 = ms2;           // call MyString& operator=(const MyString& rhs) &

    cout << endl;
    ms1 = "hello";
    ms2 = "world";
    cout << endl;
    MyString ret = (ms1 + ms2).sorted(); // call MyString sorted() &&
    MyString ret2 = ms1.sorted(); // call MyString sorted() const &

    return 0;
}
