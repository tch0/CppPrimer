#include <memory> // for smart pointers
#include <string>
#include <iostream>
using namespace std;

class TestClass
{
public:
    TestClass() = default;
    ~TestClass() {cout << "TestClass destructor called~" << endl;}
    void hello() {cout << "Hello from TestClass::hello()" << endl;}
};

unique_ptr<string> getAString(const string& str)
{
    return unique_ptr<string>(new string(str));
}

int main(int argc, char const *argv[])
{
    // shared_ptr & weak_ptr
    shared_ptr<string> sp = make_shared<string>("hello");
    cout << sp << endl;
    cout << *sp << endl;
    cout << sp.use_count() << endl;
    sp.reset(new string("world"));

    {
        weak_ptr<string> wp(sp);
        cout << wp.use_count() << endl;
        cout << (wp.expired() ? "wp is expired" : "wp is not expired") << endl;
        shared_ptr<string> sp2 = wp.lock();
        cout << sp2.use_count() << endl;
        if (sp2)
        {
            cout << *sp2 << endl;
            cout << *sp2.get() << endl;
            cout << (sp2.unique() ? "sp2 is unique" : "sp2 is not unique") << endl;
        }
    }
    cout << sp.use_count() << endl;

    // unique_ptr
    unique_ptr<string> up = getAString("hello");
    cout << *up << endl;
    unique_ptr<string> up2(new string("world"));
    up.swap(up2);
    cout << *up << " " << *up2 << endl;
    up.release();

    // using unique_ptr manage dynamic array
    unique_ptr<TestClass[]> upIntArr(new TestClass [10] {});
    upIntArr[5].hello();
    upIntArr.reset(); // free the memory that new allocated, will use delete [] instead of simply delete

    // don't use auto_ptr in new code, it's legacy
    return 0;
}
