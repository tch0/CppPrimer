#include <iostream>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
    int sum = 0, value = 0;
    while (cin >> value) // Ctrl+D/Ctrl+Z(Windows) for EOF
    {
        sum += value;
    }
    cout << sum << endl;
    return 0;
}