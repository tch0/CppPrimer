#include <iostream>
#include <string>
using namespace std;

// value-like class
class HasPtr
{
    friend ostream& operator<<(ostream&os, const HasPtr& obj);
    friend void swap(HasPtr& lhs, HasPtr& rhs);
private:
    string *ps;
    int i;
public:
    HasPtr(const string & s = string()) : ps(new string(s)), i(0) {}
    HasPtr(const HasPtr & p) : ps(new string(*p.ps)), i(p.i) {}
    HasPtr(HasPtr && p) noexcept : ps(p.ps), i(p.i) { p.ps = nullptr; } // move constructor
    HasPtr& operator=(HasPtr rhs); // copy and swap assignment, as copy assignment operator and move assignment operator
    ~HasPtr() {delete ps;}
    void setString(const string& str)
    {
        *ps = str;
    }
};

// copy and swap, self-assignment is considered automatically
// pass rhs by value instead of by reference
HasPtr& HasPtr::operator=(HasPtr rhs)
{
    swap(*this, rhs);
    return *this;
}

ostream& operator<<(ostream&os, const HasPtr& obj)
{
    os << "HasPtr : " << *obj.ps << " " << obj.i << endl;
    return os;
}

// inline for optimization
inline void swap(HasPtr& lhs, HasPtr& rhs)
{
    using std::swap; // this is important
    swap(lhs.ps, rhs.ps); // will call std::swap
    swap(lhs.i, rhs.i); // will call std::swap too
}

int main(int argc, char const *argv[])
{
    HasPtr obj("hello");
    HasPtr obj2;
    obj2 = obj;
    obj2.setString("world");
    cout << obj;
    cout << obj2;
    return 0;
}
