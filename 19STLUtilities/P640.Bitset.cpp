#include <iostream>
#include <string>
#include <bitset> // for bitset
using namespace std;


// index like the bit of unsigned int

int main(int argc, char const *argv[])
{
    bitset<8> b(0xf0);
    cout << b[0] << endl;
    cout << b[7] << endl;
    cout << b << endl;
    cout << ~b << endl;
    cout << (b ^ bitset<8>(0x0f)) << endl;
    cout << b.flip(0) << endl;
    cout << b.to_ulong() << endl;
    return 0;
}
