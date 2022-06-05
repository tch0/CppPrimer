#include <iostream>
#include <new>
#include <cstdlib>
#include <string>
using namespace std;

// overload operator new and delete
// operator new allocate memory space
// operator delete free memory space

// new expression first call the library function operator new, and construct the object
// delete expression first destruct the object, then call library function operator delete

// it will call your operator new and delete if you overload the function

// usually, do not overload operator new/delete

void* operator new(size_t size)
{
    cout << "call void* operator new(size_t size), size is " << size << endl;
    if (void* mem = malloc(size))
    {
        return mem;
    }
    else
    {
        throw bad_alloc();
    }
}

void operator delete(void* mem, size_t size) noexcept
{
    cout << "call void operator delete(void* mem) noexcept, size is" << size << endl;
    free(mem);
}

// overload nothrow version of operator new and delete
// implement with C malloc and free
void* operator new(size_t size, const nothrow_t&) noexcept
{
    cout << "call void* operator new(size_t size, const nothrow_t&) noexcept, size is " << size << endl;
    return malloc(size);
}

void operator delete(void* mem, size_t size, const nothrow_t&) noexcept
{
    cout << "call void operator delete(void* mem, const nothrow_t&) noexcept, size is " << size << endl;
    free(mem);
}

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
private:
    string s;
};

// member function version of overloaded operator new/delete
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
    static void* operator new(size_t size)
    {
        cout << "call static void* Bar::operator new(size_t size), size is " << size << endl;
        return malloc(size);
    }
    static void operator delete(void* mem, size_t size) noexcept // size is optional
    {
        cout << "call static void Bar::operator delete(void* mem) noexcept, size is " << size << endl;
        free(mem);
    }
private:
    double d;
};


// overload ::operator new/delete
void* operator new [](size_t size)
{
    cout << "call void* operator new [](size_t size), size is " << size << endl;
    return malloc(size);
}

void operator delete [](void* mem, size_t size) noexcept
{
    cout << "call void operator delete [](void* mem) noexcept, size is" << size << endl;
    free(mem);
}

int main(int argc, char const *argv[])
{
    // nothrow version
    Foo* foo = new (nothrow) Foo(); // will call operator new(size_t, nothrow_t)
    delete foo;
    cout << endl;

    // normal version, using new and delete operator
    Foo* foo2 = new Foo();
    delete foo2;
    cout << endl;
    
    // member function version
    Bar* bar = new Bar();
    /*
    // equal to
    try
    {
        void* bar = operator new(sizeof(Bar));
        Bar* p = static_cast<Foo*>(mem);
        p->Foo::Foo(); // if new[], will construct N times for N objects
    }
    */
    delete bar;
    /*
    // equal to
    p->~Foo(); // if delete [], will destruct N times for N objects
    operator delete(sizeof(Bar));
    */
    cout << endl;

    // new/delete []
    // the size that send to operator new[] is sizeof(Foo)*1 + sizeof(size_t), which is 40.
    Foo* foo3 = new Foo[1];
    delete[] foo3;
    return 0;
}
