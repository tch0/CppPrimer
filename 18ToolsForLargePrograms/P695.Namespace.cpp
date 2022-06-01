#include <iostream>
#include <string>
#include <tuple>

namespace mystd
{
int val = 10;
} // no ;

namespace mystd
{
int key = 5;
void foo();
template<typename T> struct bar;
template<> struct bar<bar<int>>;
class buz {};
}

void mystd::foo()
{
    std::cout << "void mystd::foo()" << std::endl;
}

// define outside the namespace, just like member function of class
template<typename T>
struct mystd::bar
{
};

// template specialization outside the namespace
template<>
struct mystd::bar<mystd::bar<int>>
{
void qux(buz b) // no we are inside the mystd namespace, buz is visible
{
    std::cout << "void mystd::bar<mystd::bar<int>>::qux(buz b)" << std::endl;
}
};

// nested namespace
namespace mystd
{

// inline namespace
inline namespace Version2
{
int version = 2;
}

namespace Version1
{
int version = 1;
}

}

// unnamed namespace : to replace static global declarations
namespace
{
int version = 3;
}

// namespace alias
namespace m1 = mystd::Version1;

// using declaration
// using std::cout;

// using directive
// using namespace std;

int main(int argc, char const *argv[])
{
    mystd::foo();
    mystd::bar<mystd::bar<int>>().qux(mystd::buz());
    std::cout << mystd::version << std::endl;
    std::cout << mystd::Version1::version << std::endl;
    std::cout << version << std::endl;
    std::cout << m1::version << std::endl;

    // using deirective, inject names to the outter domain of this domain.
    // conflict is allowed, but can not use these conflict names by just name, must with namespace to resolve.
    using namespace std;
    int endl = 10; // will override endl in std, like endl is added to global namespace (actually not, ::endl is not same with endl here).
    std::cout << endl << std::endl;

    // using declaration: just inject name to this domain.
    using std::cout;
    // int cout = 10; // name conflict with std::cout.
    // std::cout << cout << std::endl;

    // name lookup before type check
    return 0;
}
