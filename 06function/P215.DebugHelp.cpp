#include <iostream>
#include <cassert>
#include <string>

using namespace std;

// default NDEBUG not defined, assert will check.
// if defined NDEBUG, assert will be a empty. define it in release version if you use assert.
// g++ -D NDEUBG to define NDBUG or using #define
int main(int argc, char const *argv[])
{
    string name;
    assert(name.size() == 0);
#ifdef NDEBUG
    cout << "NDEBUG defined!" << endl;
#else
    // debug mode
    cout << "NDEBUG not defined!" << endl;
    cout << __func__ << endl;
    cout << __FILE__ << endl;
    cout << __LINE__ << endl;
    cout << __TIME__ << endl;
    cout << __DATE__ << endl;
#endif
    return 0;
}
