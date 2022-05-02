#include <iostream>
#include <initializer_list>
using namespace std;

// 1. initializer_list
void printParams(initializer_list<string> msg)
{
    for (auto& s : msg) // const string& s : msg
    {
        cout << s << " ";
    }
}

// 2. variadic template

// 3. from C, in <cstdarg>, only can using for bulit-in types

int main(int argc, char const *argv[])
{
    printParams({"hello", "world", "yes"});
    return 0;
}