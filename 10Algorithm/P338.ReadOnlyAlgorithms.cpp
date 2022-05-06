#include <vector>
#include <deque>
#include <array>
#include <string>
#include <list>
#include <algorithm>
#include <iostream>
#include <numeric> // some numeric algorithms
using namespace std;

int main(int argc, char const *argv[])
{
    vector<int> vec;
    for (int i = 0; i <= 100; i++)
    {
        vec.push_back(i);
    }
    // find
    auto iter = find(vec.begin(), vec.end(), 50);
    cout << iter - vec.begin() << endl; // 50
    // count
    vec.push_back(0);
    cout << count(vec.begin(), vec.end(), 0) << endl; // 2
    // accumulate
    cout << accumulate(vec.begin(), vec.end(), 0) << endl; // 5050
    
    // equal, accept two sequences
    int arr[10] = {10};
    fill(begin(arr), end(arr), 100);
    list<int> list1(10, 100);
    cout << (equal(begin(arr), end(arr), list1.begin()) ? "equal" : "not equal") << endl; // making sure list1 is as much as arr at least is programmer's responsibility
    return 0;
}
