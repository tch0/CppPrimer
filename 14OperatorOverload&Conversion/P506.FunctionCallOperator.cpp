#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

template<typename IterType>
void printElements(IterType b, IterType e)
{
    cout << "Elements: ";
    for (auto iter = b; iter != e; iter ++)
    {
        cout << *iter << " ";
    }
}

template<typename ContainerType>
void printAllElements(ContainerType c)
{
    printElements(begin(c), end(c));
}

int main(int argc, char const *argv[])
{
    vector<int> vec;
    for (int i = 0; i < 100; i ++)
    {
        vec.push_back(i);
    }
    int A[] = {1};
    sort(vec.begin(), vec.end(), greater<int>());
    printAllElements(vec);
    return 0;
}
