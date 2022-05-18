#include <iostream>
#include <memory>
#include <functional>
using std::cout;
using std::endl;

template<typename T>
class shared_ptr
{
public:
    using element_type = T;
    shared_ptr();
    shared_ptr(std::nullptr_t p);
    template<typename Y>
    explicit shared_ptr(Y* p); // must construct from pointer explicitly
    template<typename Y, typename Deleter>
    shared_ptr(Y* p, Deleter d);
    template<class Deleter>
    shared_ptr(std::nullptr_t p, Deleter d);
    shared_ptr(const shared_ptr<T>& sp);
    template<typename Y>
    shared_ptr(const shared_ptr<Y>& sp);
    shared_ptr(shared_ptr<T>&& sp);
    template<typename Y>
    shared_ptr(shared_ptr<Y>&& sp);
    shared_ptr& operator=(const shared_ptr<T>& sp);
    template<typename Y>
    shared_ptr& operator=(const shared_ptr<Y>& sp);
    shared_ptr& operator=(shared_ptr<T>&& sp);
    template<typename Y>
    shared_ptr& operator=(shared_ptr<Y>&& sp);
    ~shared_ptr();

    // modifiers
    void reset();
    template<typename Y>
    void reset(Y* p);
    template<typename Y, typename Deleter>
    void reset(Y* p, Deleter d);
    void swap(shared_ptr& sp);

    // Observers
    T* get() const;
    T& operator*() const;
    T* operator->() const;
    long use_count() const;
    bool unique() const; // C++20 deprecated
    explicit operator bool() const;
private:
    // auxiliary function
    void decRefCount();
private:
    T* data;
    long* use; // if data is nullptr, use should also be nullptr.
    std::function<void(T*)> deleter;
};

// Non-member functions
template<class T, class... Args>
shared_ptr<T> make_shared(Args&&... args);

template <class T>
std::ostream& operator<<(std::ostream& os, const std::shared_ptr<T>& ptr);

template<class T>
void swap(std::shared_ptr<T>& lhs, std::shared_ptr<T>& rhs);

// auxiliary function
template<typename T>
void shared_ptr<T>::decRefCount()
{
    if (data && --*use == 0)
    {
        if (deleter)
            deleter(data);
        else
            delete data;
        delete use;
    }
    data = nullptr;
    use = nullptr;
    deleter = nullptr;
}

// constructor and copy control
template<typename T>
shared_ptr<T>::shared_ptr() : data(nullptr), use(nullptr), deleter(nullptr)
{
}

template<typename T>
shared_ptr<T>::shared_ptr(std::nullptr_t p) : shared_ptr()
{
}

template<typename T>
template<typename Y>
shared_ptr<T>::shared_ptr(Y* p) : data(p), use(nullptr), deleter(nullptr)
{
    if (data)
        use = new long(1);
}

template<typename T>
template<typename Y, typename Deleter>
shared_ptr<T>::shared_ptr(Y* p, Deleter d) : data(p), use(nullptr), deleter(d)
{
    if (data)
        use = new long(1);
}

template<typename T>
template<class Deleter>
shared_ptr<T>::shared_ptr(std::nullptr_t p, Deleter d) : data(nullptr), use(nullptr), deleter(d)
{
}

template<typename T>
shared_ptr<T>::shared_ptr(const shared_ptr<T>& sp) : data(sp.data), use(sp.use), deleter(sp.deleter)
{
    if (use)
        ++*use;
}

template<typename T>
template<typename Y>
shared_ptr<T>::shared_ptr(const shared_ptr<Y>& sp) : data(sp.data), use(sp.use), deleter(sp.deleter)
{
}

template<typename T>
shared_ptr<T>::shared_ptr(shared_ptr<T>&& sp) : data(sp.data), use(sp.use), deleter(sp.deleter)
{
    sp.decRefCount();
}

template<typename T>
template<typename Y>
shared_ptr<T>::shared_ptr(shared_ptr<Y>&& sp) : data(sp.data), use(sp.use), deleter(sp.deleter)
{
    sp.decRefCount();
}

template<typename T>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr<T>& sp)
{
    decRefCount();
    data = sp.data;
    use = sp.use;
    deleter = sp.deleter;
    if (use)
        ++*use;
}

template<typename T>
template<typename Y>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr<Y>& sp)
{
    decRefCount();
    data = sp.data;
    use = sp.use;
    deleter = sp.deleter;
    if (use)
        ++*use;
}

template<typename T>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr<T>&& sp)
{
    decRefCount();
    data = sp.data;
    use = sp.use;
    deleter = sp.deleter;
    if (use)
        ++*use;
    sp.decRefCount();
}

template<typename T>
template<typename Y>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr<Y>&& sp)
{
    decRefCount();
    data = sp.data;
    use = sp.use;
    deleter = sp.deleter;
    if (use)
        ++*use;
    sp.decRefCount();
}

template<typename T>
shared_ptr<T>::~shared_ptr()
{
    decRefCount();
}

// modifiers
template<typename T>
void shared_ptr<T>::reset()
{
    decRefCount();
}

template<typename T>
template<typename Y>
void shared_ptr<T>::reset(Y* p)
{
    decRefCount();
    data = p;
    if (data)
        use = new long(1);
}

template<typename T>
template<typename Y, typename Deleter>
void shared_ptr<T>::reset(Y* p, Deleter d)
{
    decRefCount();
    data = p;
    if (data)
        use = new long(1);
    deleter = d;
}

template<typename T>
void shared_ptr<T>::swap(shared_ptr<T>& sp)
{
    std::swap(sp.data, data);
    std::swap(sp.use, use);
    std::swap(sp.deleter, deleter);
}

// Observers
template<typename T>
T* shared_ptr<T>::get() const
{
    return data;
}

template<typename T>
T& shared_ptr<T>::operator*() const
{
    return *data;
}

template<typename T>
T* shared_ptr<T>::operator->() const
{
    return data;
}

template<typename T>
long shared_ptr<T>::use_count() const
{
    return data == nullptr ? 0 : *use;
}

template<typename T>
bool shared_ptr<T>::unique() const // C++20 deprecated
{
    return use_count() == 1;
}

template<typename T>
shared_ptr<T>::operator bool() const
{
    return data != nullptr;
}

// Non-member functions
template<class T, class... Args>
shared_ptr<T> make_shared(Args&&... args)
{
    return shared_ptr<T>(new T(args...)); // todo
}

template <class T>
std::ostream& operator<<(std::ostream& os, const std::shared_ptr<T>& ptr)
{
    os << ptr.get();
    return os;
}

template<class T>
void swap(std::shared_ptr<T>& lhs, std::shared_ptr<T>& rhs)
{
    lhs.swap(rhs);
}

int main(int argc, char const *argv[])
{
    shared_ptr<int> sp = make_shared<int>(1.0);
    cout << sp.use_count() << endl;
    cout << sp.unique() << endl;
    sp.reset();
    cout << sp.use_count() << endl;
    cout << sp.get() << endl;
    return 0;
}
