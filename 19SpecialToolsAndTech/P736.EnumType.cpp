#include <iostream>
using namespace std;

// unscoped enumeration (from C) : enum
// scoped enumeration: enum class

// forward declaration: need specify underlying type for unscoped enumeration
enum class WeekDay;
enum WeekDay2 : int;

// add a integer type to specify the bottom integer type of this enum, default is int for scoped enumeration.
enum class WeekDay
{
    Mon = 1, Tue, Thr, Wed, Fri, Sat, Sun
};

enum WeekDay2 : int
{
    Mon = 1, Tue, Thr, Wed, Fri, Sat, Sun
};

int main(int argc, char const *argv[])
{
    cout << Mon << endl;
    return 0;
}
