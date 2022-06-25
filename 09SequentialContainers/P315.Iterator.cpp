#include <string>
#include <vector>
#include <deque>
#include <array>
#include <list>
#include <forward_list>
#include <iostream>
using namespace std;

template<typename T>
void printTypeString (const vector<T>&) { cout << "vector: "; }
template<typename T>
void printTypeString (const deque<T>&) { cout << "deque: "; }
template<typename T>
void printTypeString (const list<T>&) { cout << "list: "; }
template<typename T>
void printTypeString (const forward_list<T>&) { cout << "forward_list: "; }
template<typename T, size_t size>
void printTypeString (const array<T, size>&) { cout << "array[" << size << "]: "; }

template<typename ContainerType>
void printContent(const ContainerType& container)
{
    printTypeString(container);
    for (const auto& elem : container)
    {
        cout << elem << " ";
    }
    cout << endl;
}

void printContent(const string& str)
{
    cout << "string: " << str << endl;
}

void deleteEvenAndDoubleOdd(vector<int>& vec)
{
    auto iter = vec.begin();
    while (iter != vec.end()) // do not save end iterator
    {
        if (*iter % 2 == 1)
        {
            iter = vec.insert(iter, *iter);
            iter += 2;
        }
        else
        {
            iter = vec.erase(iter);
        }
    }
}

// search method of string
void findAllNumberInAString(const string& str)
{
    string::size_type pos = 0;
    while ((pos = str.find_first_of("0123456789", pos)) != string::npos)
    {
        cout << "found number at index : " << pos << ", element is " << str[pos] << endl;
        pos ++;
    }
}

int main(int argc, char const *argv[])
{
    vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    deleteEvenAndDoubleOdd(vec);
    printContent(vec);
    findAllNumberInAString("1asdfhjas12934h234k2j4h21kj4g12kj3h42kj34");
    return 0;
}
