#include <iostream>
#include <string>
using namespace std;

using Arr10_t = int[10];
Arr10_t arr;
using Arr10p_t = int(*)[10];

// return a pointer to array
// 1
int (*getArr(int a))[10]
{
    return &arr;
}

// 2
Arr10_t* getArr2(int a)
{
    return &arr;
}

// 3
auto getArr3(int a) -> int(*)[10]
{
    return &arr;
}

// 4
decltype(arr)* getArr4(int a) // or just decltype(&arr)
{
    return &arr;
}

// 5
Arr10p_t getArr5(int a)
{
    return &arr;
}

int main(int argc, char const *argv[])
{
    return 0;
}