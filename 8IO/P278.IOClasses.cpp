#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;



int main(int argc, char const *argv[])
{
    int ival;
    while ((cin >> ival).good()) // equal to : cin >> ival, !(cin >> ival).fail()
    {
        cout << ival << endl;
    }
    cin.clear();
    string s;
    while (cin >> s)
    {
        cout << s << endl; // end line, insert a CRLF and flush
    }
    cout << "end" << ends; // end string, insert a \0 and flush
    cout << flush; // flush the buffer
    return 0;
}
