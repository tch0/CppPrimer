#include <iostream>
#include <vector>
#include <initializer_list>
#include <memory>
using namespace std;

template<typename T = int>
class Blob
{
public:
    using value_type = T;
    using size_type = typename vector<T>::size_type; // use typename in template to specify size_type is a type instead of a static member.
    Blob();
    Blob(initializer_list<T> il);
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    // add and delete element
    void push_back(const T& t) { data->push_back(t); }
    void push_back(T&& t) { data->push_back(t); }
    void pop_back();
    // visit element
    T& back();
    const T& back() const;
    T& front();
    const T& front() const;
    T& operator[](size_type i);
    const T& operator[](size_type i) const;
private:
    shared_ptr<vector<T>> data;
    void check(size_type i, const string& msg) const;
};

// the class name is Blob<T> not Blob.
template<typename T>
Blob<T>::Blob() : data(make_shared<vector<T>>())
{
}

template<typename T>
Blob<T>::Blob(initializer_list<T> il) : data(make_shared<vector<T>>(il))
{
}

template<typename T>
void Blob<T>::pop_back()
{
    check(0, "pop_back on empty Blob");
    data->pop_back();
}

template<typename T>
T& Blob<T>::back()
{
    check(0, "back on empty Blob");
    return data->back();
}

template<typename T>
const T& Blob<T>::back() const
{
    check(0, "back on empty Blob");
    return data->back();
}

template<typename T>
T& Blob<T>::front()
{
    check(0, "front on empty Blob");
    return data->front();
}

template<typename T>
const T& Blob<T>::front() const
{
    check(0, "front on empty Blob");
    return data->front();
}

template<typename T>
T& Blob<T>::operator[](size_type i)
{
    check(i, "subscript out of range");
    return (*data)[i];
}

template<typename T>
const T& Blob<T>::operator[](size_type i) const
{
    check(i, "subscript out of range");
    return (*data)[i];
}

template<typename T>
void Blob<T>::check(size_type i, const string& msg) const
{
    if (i >= data->size())
        throw std::out_of_range(msg);
}

// template alias of a family of type
template<typename T>
using BlobP = Blob<T>*;

int main(int argc, char const *argv[])
{
    Blob<string> blobStr = {"a", "an", "the"};
    BlobP<string> pBlob = &blobStr; // Blob<string>*

    Blob<> blobi = {1, 2, 3}; // use default type argument int (<>)
    return 0;
}
