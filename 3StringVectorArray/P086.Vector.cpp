#include <iostream>
#include <vector>
#include <string>
using namespace std;

template<typename T>
ostream& operator<<(ostream& os, vector<T> vec)
{
    cout << "vector: ";
    for (const auto& elem : vec)
    {
        cout << elem << " ";
    }
    return os;
}

int main(int argc, char const *argv[])
{
    vector<int> vec1(10, 100);
    vector<int> vec2(vec1);
    cout << vec2 << endl;
    return 0;
}