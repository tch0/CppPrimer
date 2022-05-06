#include <vector>
#include <array>
#include <deque>
#include <list>
#include <string>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <iterator>
using namespace std;

// auxiliary functions
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

template<typename ArrOrContainer>
void printAllElements(const ArrOrContainer& container)
{
    printElements(begin(container), end(container));
}

int main(int argc, char const *argv[])
{
    // fill
    int arr[20] = {};;
    fill(begin(arr), end(arr), 99);
    printElements(begin(arr), end(arr));
    // fill_n
    fill_n(begin(arr), sizeof(arr)/sizeof(int), 100);
    printElements(begin(arr), end(arr));

    // back_inserter, an insert iterator in <iterator>
    // accept a container, get a back_inserter that bind with this container
    vector<int> vec; // empty vector
    auto it = back_inserter(vec);
    *it = 42; // just like vec.push_back(42);
    fill_n(it, 10, 100); // 
    printElements(vec.begin(), vec.end());

    // copy
    vector<int> vec2;
    copy(begin(vec), end(vec), back_inserter(vec2));
    printAllElements(vec2);

    // replace, replace_copy (copy version of replace, not modify in-place but copy result to a new container)
    replace(begin(vec), end(vec), 42, 98);
    printAllElements(vec);
    vector<int> vec3;
    replace_copy(begin(vec), end(vec), back_inserter(vec3), 96, 1024); // result is in vec3
    printAllElements(vec3);
    return 0;
}
