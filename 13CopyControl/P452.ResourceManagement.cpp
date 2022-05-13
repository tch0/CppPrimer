#include <iostream>
#include <string>
using namespace std;

// value-like class
class HasPtr
{
    friend ostream& operator<<(ostream&os, const HasPtr& obj);
private:
    string *ps;
    int i;
public:
    HasPtr(const string & s = string()) : ps(new string(s)), i(0) {}
    HasPtr(const HasPtr & p) : ps(new string(*p.ps)), i(0) {}
    HasPtr& operator=(const HasPtr&);
    ~HasPtr() {delete ps;}
    void setString(const string& str)
    {
        *ps = str;
    }
};

// must think about self-assignment
HasPtr& HasPtr::operator=(const HasPtr& rhs)
{
    auto newp = new string(*rhs.ps);
    delete ps;
    ps = newp;
    i = rhs.i;
    return *this;
}

ostream& operator<<(ostream&os, const HasPtr& obj)
{
    os << "HasPtr : " << *obj.ps << " " << obj.i << endl;
    return os;
}


// pointer like class
class HasPtrP
{
    friend ostream& operator<<(ostream&os, const HasPtrP& obj);
private:
    string* ps;
    int i;
    size_t* use;
public:
    HasPtrP(const string& s = string()) : ps(new string(s)), i(0), use(new size_t(1)) {}
    HasPtrP(const HasPtrP & p) : ps(p.ps), i(p.i), use(p.use) { ++ *use;} // increase reference count
    HasPtrP& operator=(const HasPtrP& rhs);
    ~HasPtrP();
    void setString(const string& str)
    {
        *ps = str;
    }
};

HasPtrP& HasPtrP::operator=(const HasPtrP& rhs)
{
    ++*rhs.use;
    if (--*use == 0)
    {
        delete ps;
        delete use;
    }
    ps = rhs.ps;
    i = rhs.i;
    use = rhs.use;
    return *this;
}

HasPtrP::~HasPtrP()
{
    if (--*use == 0)
    {
        delete ps;
        delete use;
    }
}

ostream& operator<<(ostream&os, const HasPtrP& obj)
{
    os << "HasPtrP : " << *obj.ps << " " << obj.i << " [reference count: " << *obj.use << "]" << endl;
    return os;
}

int main(int argc, char const *argv[])
{
    HasPtr obj("hello");
    HasPtr obj2;
    obj2 = obj;
    obj2.setString("world");
    cout << obj;
    cout << obj2;

    HasPtrP pobj("hello");
    {
        HasPtrP pobj2(pobj);
        cout << pobj2;
        pobj2.setString("world");
        cout << pobj;
    }
    cout << pobj << endl;
    HasPtrP pobj3;
    cout << pobj3;
    pobj3 = pobj;
    cout << pobj3;
    return 0;
}
