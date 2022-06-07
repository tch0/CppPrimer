#include <iostream>
#include <cstring>
using namespace std;

// extern "C"
// macro: __cplusplus

extern "C"
void foo()
{
    cout << "extern \"C\" void foo()" << endl;
}

extern "C" typedef void(*FC)();

void bar()
{
    cout << "void bar()" << endl;
}

int main(int argc, char const *argv[])
{
    1;
    FC cpf = foo;
    cpf();
    void (*pf)() = bar;
    pf = foo; // theoretically invalid
    pf();
    return 0;
}
