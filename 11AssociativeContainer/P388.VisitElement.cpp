#include <utility>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

int main(int argc, char const *argv[])
{
    // [], at only can be used in map/unorder_map
    map<string, string> dict{{"hello", "world"}, {"yes", "no"}};
    cout << "hello: " <<  dict["hello"] << endl;
    cout << "yes: " << dict.at("yes") << endl; 

    // lower_bound, upper_bound, equal_range, only can be used in ordered container((multi_)map/set)
    multimap<string, int> m{{"hello", 1}, {"hello", 2}, {"yes", 100}, {"no", 99}};
    auto res = m.equal_range("hello");
    cout << "all values of key hello: ";
    for (auto iter = res.first; iter != res.second; iter++)
    {
        cout << iter->second << " ";
    }
    cout << endl;

    // find, count
    cout << "count of key hello: " << m.count("hello") << endl;
    int resCount = m.count("hello");
    for (auto iter = m.find("hello"); iter != m.end() && resCount > 0; resCount--, iter ++)
    {
        cout << "hello: " << iter->second << endl;
    }
    return 0;
}
