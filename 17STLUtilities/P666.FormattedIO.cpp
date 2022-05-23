#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;



int main(int argc, char const *argv[])
{
    // IO manipulator
    // bool
    cout << boolalpha << true << " " << false << endl
         << noboolalpha << true << " " << false << endl;
    // integers : radix, case, base
    cout << hex << 20 << " " << oct << 20 << " " << showbase << uppercase << hex << 20 << endl;
    cout << noshowbase << nouppercase << dec;
    // float point number
    // precision
    cout << "precision: " << cout.precision() << sqrt(2.0) << endl;
    cout.precision(12);
    cout << sqrt(2.0) << endl
         << setprecision(3) << sqrt(2.0) << endl;
    // point
    cout << showpoint << 1.0 << endl;
    // format
    cout << scientific << 1.0001 << endl;
    // ...etc
    // align
    cout << setfill('='); // set character that fill blanks
    cout << setw(10) << left << "hello" << endl;    
    return 0;
}
