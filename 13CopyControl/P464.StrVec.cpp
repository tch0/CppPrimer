#include <string>
#include <iostream>
#include <memory>
using namespace std;

class StrVec
{
private:
    static allocator<string> alloc;
    string* elements; // point to first element
    string* firstFree; // off the end of elements
    string* cap; // off the end of allocated memory
    void checkNAlloc()
    {
        if (size() == capcacity())
        { 
            reallocate();
        }
    }
    pair<string*, string*> allocNCopy(const string* b, const string* e);
    void free();
    void reallocate();
public:
    StrVec() : elements(nullptr), firstFree(nullptr), cap(nullptr) {}
    StrVec(const StrVec& vec);
    StrVec(StrVec&& vec) noexcept; // move constructor, must has noexcept
    StrVec& operator=(const StrVec& rhs);
    StrVec& operator=(StrVec&& rhs) noexcept; // move assignment operator, also must be noexcept
    ~StrVec();
    void push_back(const string& elem);
    void push_back(string&& elem); // rvalue reference version of push_back
    size_t size() const { return firstFree - elements; }
    size_t capcacity() const { return cap - elements; }
    string* begin() const { return elements; }
    string* end() const { return firstFree; }
};

// definition of static member
allocator<string> StrVec::alloc;

// return (newbegin, newend)
pair<string*, string*> StrVec::allocNCopy(const string* b, const string* e)
{
    auto data = alloc.allocate(e - b);
    return {data, uninitialized_copy(b, e, data)};
}

void StrVec::free()
{
    if (elements)
    {
        for (auto p = firstFree; p != elements;)
        {
            alloc.destroy(--p);
        }
        alloc.deallocate(elements, cap - elements);
    }
}

void StrVec::reallocate()
{
    // allocate new memory
    auto newCapacity = size() ? 2 * size() : 1;
    auto newdata = alloc.allocate(newCapacity);

    // copy (move)
    // auto dest = newdata;
    // auto elem = elements;
    // for (size_t i = 0; i != size(); i ++)
    // {
    //     alloc.construct(dest++, std::move(*elem++)); // move construct all elements(if they have a move constructor)
    // }
    
    // or just use move iterator
    auto dest = uninitialized_copy(make_move_iterator(begin()), make_move_iterator(end()), newdata);

    // free old memory
    free();
    elements = newdata;
    firstFree = dest;
    cap = elements + newCapacity;
}

StrVec::StrVec(const StrVec& vec)
{
    auto newdata = allocNCopy(vec.begin(), vec.end());
    elements = newdata.first;
    firstFree = cap = newdata.second;
}

StrVec::StrVec(StrVec&& vec) noexcept : elements(vec.elements), firstFree(vec.firstFree), cap(vec.cap)
{
    elements = firstFree = cap = nullptr;
}

StrVec& StrVec::operator=(const StrVec& rhs)
{
    auto data = allocNCopy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    firstFree = cap = data.second;
    return *this;
}

StrVec& StrVec::operator=(StrVec&& rhs) noexcept
{
    if (this != &rhs)
    {
        free();
        elements = rhs.elements;
        firstFree = rhs.firstFree;
        cap = rhs.cap;
        rhs.elements = rhs.firstFree = rhs.cap = nullptr;
    }
    return *this;
}

StrVec::~StrVec()
{
    free();
}

void StrVec::push_back(const string& elem)
{
    checkNAlloc(); // ensure there is space that can contain new elements
    alloc.construct(firstFree++, elem);
}

void StrVec::push_back(string&& elem)
{
    checkNAlloc();
    alloc.construct(firstFree++, std::move(elem));
}

template<typename IterType>
void printElements(IterType b, IterType e)
{
    cout << "Elements: ";
    for (auto iter = b; iter != e; iter++)
    {
        cout << *iter << " ";
    }
    cout << endl;
}

template<typename ConatinerType>
void printAllElements(ConatinerType container)
{
    printElements(container.begin(), container.end());
}

int main(int argc, char const *argv[])
{
    StrVec vec;
    cout << vec.size() << " " << vec.capcacity() << endl;
    for (auto i = 0; i < 100; i ++)
    {
        vec.push_back(to_string(i));
    }
    cout << vec.size() << " " << vec.capcacity() << endl;

    StrVec vec2 = vec;
    printAllElements(vec2);

    StrVec vec3;
    printAllElements(vec3);
    vec3 = vec2;
    printAllElements(vec3);
    return 0;
}
