#include <string>
#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

// a good implementation of generating a random vector of 100 elements
// the random engine and distribution should be static to keep status through different calls.
vector<unsigned> randomVector()
{
    static default_random_engine e;
    static uniform_int_distribution<unsigned> u;
    vector<unsigned> vec;
    for (size_t i = 0; i < 100; ++i)
    {
        vec.push_back(u(e));
    }
    return vec;
}

int main(int argc, char const *argv[])
{
    // random engine
    default_random_engine e(0); // give 0 as seed
    e.seed(100); // give 100 as new seed
    for (size_t i = 0; i < 100; ++i)
    {
        cout << e() << " ";
    }
    cout << endl;
    cout << e.max() << " " << e.min() << endl; // 2^31-2 1

    // random-number distribution
    vector<unsigned> vec;
    uniform_int_distribution<unsigned> u(0, 99);
    default_random_engine e2;
    for (size_t i = 0; i < 100; ++i)
    {
        auto elem = u(e);
        cout << elem << " ";
        vec.push_back(elem);
    }
    cout << endl;
    sort(vec.begin(), vec.end());
    for (auto elem : vec)
    {
        cout << elem << " ";
    }
    cout << endl;

    // float random number (like between 0.0 and 1.0)
    default_random_engine e3;
    uniform_real_distribution<> ur(0, 1); // default result type is double
    for (size_t i = 0; i < 100; ++i)
    {
        cout << ur(e) << " ";
    }
    cout << endl;

    // normal distribution
    default_random_engine e4;
    normal_distribution<> n(4, 1.5); // average: 4, standard deviation: 1.5
    vector<unsigned> vals(9);
    for (size_t i = 0; i < 200; ++i)
    {
        unsigned v = lround(n(e));
        if (v < vals.size())
        {
            ++vals[v];
        }
    }
    for (size_t i = 0; i < vals.size(); ++i)
    {
        cout << i << ": " << string(vals[i], '*') << endl;
    }
    return 0;
}
