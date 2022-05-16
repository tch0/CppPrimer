#include <iostream>
using namespace std;

class Foo
{
public:
    Foo()
    {
        cout << "Foo()" << endl;
    }
    ~Foo()
    {
        cout << "~Foo()" << endl;
    }
};

class Bar
{
public:
    Bar()
    {
        cout << "Bar()" << endl;
    }
    ~Bar()
    {
        cout << "~Bar()" << endl;
    }
};

class Base
{
public:
    Base()
    {
        cout << "Base()" << endl;
    }
    Base(const Base& b) : foo(b.foo)
    {
        cout << "Base(const Base& b)" << endl;
    }
    Base(Base&& b) : foo(std::move(b.foo))
    {
        cout << "Base(Base&& b)" << endl;
    }
    virtual ~Base()
    {
        cout << "virtual ~Base()" << endl;
        cout << "========= ";
        buz(); // caution: this will call Base::buz() instead of Derived::buz(), virtual function call in destructor will match the class of the executing destructor.
    }
    Base& operator=(const Base& b)
    {
        foo = b.foo;
        cout << "Base& operator=(const Base& b)" << endl;
        return *this;
    }
    Base& operator=(Base&& b)
    {
        foo = std::move(b.foo);
        cout << "Base& operator=(Base&& b)" << endl;
        return *this;
    }
    virtual void buz()
    {
        cout << "virtual void Base::buz()" << endl;
    }
private:
    Foo foo;
};

class Derived : public Base
{
public:
    Derived()
    {
        cout << "Derived()" << endl;
    }
    Derived(const Derived& d) : Base(d), bar(d.bar)
    {
        cout << "Derived(const Derived& d)" << endl;
    }
    Derived(Derived&& d) : Base(std::move(d)), bar(std::move(d.bar)) // must call std::move explicitly, Derived&& will not match Base&& automatically
    {
        cout << "Derived(Derived&& d)" << endl;
    }
    virtual ~Derived()
    {
        cout << "virtual ~Derived()" << endl;
    }
    Derived& operator=(const Derived& d)
    {
        Base::operator=(d);
        bar = d.bar;
        cout << "Derived& operator=(const Derived& d)" << endl;
        return *this;
    }
    Derived& operator=(Derived&& d)
    {
        Base::operator=(std::move(d));
        bar = std::move(d.bar);
        cout << "Derived& operator=(Derived&& d)" << endl;
        return *this;
    }
    virtual void buz()
    {
        cout << "virtual void Derived::buz()" << endl;
    }
private:
    Bar bar;
};


int main(int argc, char const *argv[])
{
    Derived();

    {
        cout << endl;
        Derived d1;
        Derived d2(d1);
        cout << endl;
        d1 = d2;
        cout << endl;
    }
    cout << endl << "test2:" << endl;
    {
        cout << endl;
        
        Derived d1;
        cout << endl;
        // copy constructor
        Derived d2(std::move(d1));
        // copy-assignment
        cout << endl;
        d2 = Derived();
        cout << endl;
    }
    return 0;
}
