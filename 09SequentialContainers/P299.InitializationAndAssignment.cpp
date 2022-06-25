#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <array>
#include <string>
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

int main(int argc, char const *argv[])
{
    // universal initialization for all containers except array
    vector<int> vec1{10, 20, 30};
    vector<int> vec2 = vec1;
    list<int> vec3(vec2.begin(), vec2.end());
    list<int> list1{1, 2, 3, 4};
    list<int> list2 = {10, 20, 30, 40};
    forward_list<int> flist1(list2.begin(), list2.end());
    printContent(flist1);
    deque<int> dq1(10, 200);
    printContent(dq1);

    // array
    array<int, 10> arr = {};
    printContent(arr);

    cout << endl;

    // assignment and swap
    decltype(vec1) newvec;
    newvec = vec1; // same type container assignment
    printContent(newvec);

    list<int> newlist;
    newlist = {1, 2, 3}; // initializer_list
    printContent(newlist);

    // swap, move
    list<int> newlist2;
    newlist2 = {4, 5, 6};
    newlist.swap(newlist2); // swap(newlist, newlist2)
    printContent(newlist);

    // assign method: iterator scope, intializer_list, (num, value)
    deque<int> newdq;
    newdq.assign(newlist.rbegin(), newlist.rend());
    printContent(newdq);
    newdq.assign({100, 10, 1});
    printContent(newdq);
    newdq.assign(10, 99);
    printContent(newdq);
    return 0;
}