#include <iostream>
#include <string>
using namespace std;

// calculate while compiling
constexpr int getVal() // return value must be literal types.
{
    return 10 + 100;
}

constexpr int val = 10;
constexpr int val2 = getVal();

int main(int argc, char const *argv[])
{
    cout << val << " " << val2 << endl;
    return 0;
}