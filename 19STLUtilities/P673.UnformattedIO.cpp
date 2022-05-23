#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;

int main(int argc, char const *argv[])
{
    // read and write by character: get/put

    // put character to istream
    char ch;
    while (cin.get(ch))
    {
        cout.put(ch);
    }
    return 0;
}
