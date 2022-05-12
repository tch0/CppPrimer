#include <memory>
#include <vector>
#include <iostream>
#include <string>
#include <memory> // for allocator
using namespace std;
using namespace std::string_literals;

class TestClass
{
    friend ostream& operator<<(ostream& os, const TestClass& obj);
public:
    TestClass(const string& s) : str(s) {cout << "TestClass(const string& s) called ~" << endl;}
    TestClass(const TestClass& obj) : str(obj.str) { cout << "TestClass(const TestClass& obj) called ~" << endl;}
    ~TestClass() {cout << "~TestClass() called ~, inner string: " << str << endl;}
private:
    string str;
};
ostream& operator<<(ostream& os, const TestClass& obj)
{
    os << obj.str;
    return os;
}

template<typename IterType>
void printElements(IterType b, IterType e)
{
    cout << "elements: ";
    for (auto iter = b; iter != e; iter ++)
    {
        cout << *iter << " ";
    }
    cout << endl;
}

int main(int argc, char const *argv[])
{
    size_t allocSize = 10;
    allocator<TestClass> alloc;
    TestClass * const p = alloc.allocate(allocSize);
    // first 5 elements
    // allocator algorithms: copy elements to uninitialized space
    vector<TestClass> vec{"hello"s, "world"s};
    auto temp = uninitialized_copy(vec.begin(), vec.end(), p);
    uninitialized_fill_n(p, 3, "fill-string");
    // rest elements
    for (size_t i = 5; i < allocSize; i ++)
    {
        alloc.construct(p+i, "hello" + to_string(i)); // construct objects
    }
    printElements(p, p+allocSize);
    for (size_t i = 0; i < allocSize; i ++)
    {
        alloc.destroy(p+i); // destruct objects
    }
    alloc.deallocate(p, allocSize); // must destroy objects before deallocate
    return 0;
}

