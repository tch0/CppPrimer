#include <iostream>
#include <string>
using namespace std;

typedef bool pf(const string&, const string&);

bool lengthCompare(const string& s1, const string& s2)
{
    return s1.length() > s1.length () ? (s1.length() == s1.length() ? 0 : 1) : -1;
}

int main(int argc, char const *argv[])
{
    pf* cmp = lengthCompare;
    return 0;
}
