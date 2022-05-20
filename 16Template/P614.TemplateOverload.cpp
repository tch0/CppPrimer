#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

// 1
template<typename T>
string debug_rep(const T& t)
{
    ostringstream oss;
    oss << t;
    return oss.str();
}

// 2
template<typename T>
string debug_rep(T* p)
{
    ostringstream oss;
    oss << "pointer: " << p;
    if (p)
        oss << " " << debug_rep(*p);
    else
        oss << " null pointer";
    return oss.str();
}

// 3
string debug_rep(const string& s)
{
    return '"' + s + '"';
}

int main(int argc, char const *argv[])
{
    // version 1
    cout << debug_rep(10) << endl;

    // version 2
    string s("hi");
    cout << debug_rep(&s) << endl;

    // version 2
    const string* cp = &s;
    cout << debug_rep(cp) << endl;

    // version 2
    cout << debug_rep("hello") << endl;

    // version 3
    cout << debug_rep(s) << endl;
    return 0;
}
