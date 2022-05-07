#include <vector>
#include <array>
#include <deque>
#include <list>
#include <string>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <functional> // for std::bind
using namespace std;

// auxiliary functions
template<typename IterType>
void printElements(IterType b, IterType e)
{
    cout << "elements: ";
    for (auto iter = b; iter != e; iter ++)
    {
        cout << *iter << " ";
    }
    cout << endl;
}

template<typename ArrayOrContainer>
void printAllElements(const ArrayOrContainer& container)
{
    printElements(begin(container), end(container));
}

bool lengthShorter(const string& s1, const string& s2)
{
    return s1.size() < s2.size() ? true : (s1.size() == s2.size() ? s1 < s2 : false);
}

auto getShorter(const string& s1, const string& s2)
{
    return [&s1, &s2]() -> bool {return lengthShorter(s1, s2);};
}

int main(int argc, char const *argv[])
{
    vector<string> words{"the", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog's", "back"};
    stable_sort(words.begin(), words.end(), lengthShorter); // use lengthShorter to compare
    printAllElements(words);

    // find_if
    // and lambda expression
    auto resIter = find_if(words.begin(), words.end(), [](const string& str) -> bool {return str.find('\'') != string::npos;});
    printElements(resIter, words.end());

    // lambda, the type of f is main(int, const char**)::<lambda()>, but can not declare it as this type.
    auto f = [] {return 42;};
    cout << f() << endl;

    // count_if
    cout << "count of size > 3: " << count_if(words.begin(), words.end(), [](const string& str) -> bool {return str.size() > 3;}) << endl;

    // for_each
    for_each(words.begin(), words.end(), [](const string& s) {cout << s << " ";});
    cout << endl;

    cout << getShorter("yes", "no")() << endl;

    int a = 0;
    [a]() mutable {a = 42; cout << a << endl;}(); // if wanna modify the variable of value capture, use mutable

    // transform
    vector<int> vec;
    for (int i = 0; i < 10; i++)
    {
        vec.push_back(i);
    }
    auto func = [](int val) -> int { // not only a return statement, must define return type explicitly
        if (val % 2 == 1)
            return -val;
        else
            return val;
    };
    transform(vec.begin(), vec.end(), vec.begin(), func);
    printAllElements(vec);

    // std::bind
    auto foo = [] (double x, double y) -> double {return x * y;};
    auto foox = bind(foo, placeholders::_1, 10); // namespace placeholders is in <functional>
    cout << foox(42) << endl;

    // ref & cref in <functional>, bind reference/const reference variable in std::bind
    auto print = [](ostream& os, const string& s, char c){os << s << c;};
    for_each(words.begin(), words.end(), bind(print, ref(cout), placeholders::_1, ' '));
    return 0;
}
