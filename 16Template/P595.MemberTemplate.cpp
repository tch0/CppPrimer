#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <list>
using namespace std;

// member template of normal class
// to replace delete operator in unique_ptr
class DebugDelete
{
public:
    DebugDelete(ostream& s = cerr) : os(s) {}
    // member template
    template<typename T>
    void operator()(T* p) const
    {
        os << "deleting unique_ptr" << endl;
        delete p;
    }
private:
    ostream& os;
};

// member template of class template
template<typename T> class Blob; // template declaration
template<typename T>
class Blob
{
public:
    template<typename It> Blob(It b, It e);
    typename vector<T>::const_iterator begin() const { return data->begin(); }
    typename vector<T>::iterator begin() { return data->begin(); }
    typename vector<T>::const_iterator end() const { return data->end(); }
    typename vector<T>::iterator end() { return data->end(); }
private:
    shared_ptr<vector<T>> data;
};

template<typename T>
template<typename It>
Blob<T>::Blob(It b, It e)
    : data(make_shared<vector<T>>(b, e))
{
}

template<typename Container>
void printContents(const Container& c)
{
    cout << "Contents: ";
    for (auto it = c.begin(); it != c.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;
}

int main(int argc, char const *argv[])
{
    // call DebugDelete()() like delete operator
    double* dp = new double(2.0);
    DebugDelete d;
    d(dp); // call DebugDelete::operator()(double*)
    int* ip = new int(42);
    d(ip);

    // as deleter of unique_ptr
    unique_ptr<string, DebugDelete> p(new string("hello"), DebugDelete());
    p.reset();

    // member template of class template
    list<int> l{1, 2, 3, 4};
    Blob<int> b(l.begin(), l.end());
    printContents(b);
    return 0;
}
