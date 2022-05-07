#include <vector>
#include <array>
#include <deque>
#include <list>
#include <string>
#include <numeric>
#include <algorithm>
#include <functional>
#include <iterator> // for iterators
#include <iostream>
using namespace std;

// more about iterators
// 1. insert iterator
// 2. stream iterator
// 3. reverse iterator
// 4. move iterator (later)

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

int main(int argc, char const *argv[])
{
    // inserters: as output target
    // back_inserter
    vector<int> vec;
    auto it = back_inserter(vec);
    it = 42; // equals to *it = 42
    *it = 100;
    printAllElements(vec);

    // front_inserter
    deque<int> dq;
    auto iter = front_inserter(dq);
    for (int i = 0; i < 10; i ++)
    {
        *iter = i*i;
    }
    printAllElements(dq);

    // inserter
    vector<int> vec2(10, 10);
    auto viter = vec2.begin() + 5;
    auto inIter = inserter(vec2, viter);
    for (int i = 0; i < 10; i ++)
    {
        *inIter = i*i;
    }
    printAllElements(vec2);

    // stream iterator
    // istream_iterator : as input source
    istream_iterator<int> inputIter(cin);
    istream_iterator<int> eofIter; // empty istream iterator as EOF (because EOF will cause a empty istream iterator)
    vector<int> vecInput(inputIter, eofIter); // will read int from cin continuously until EOF
    printAllElements(vecInput);

    // ostream_iterator, just like insert_iterator, as output target
    list<string> outList = {"The", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog's", "back"};
    ostream_iterator<string> outputIter(cout, " "); // ouput " " as separator
    copy(outList.begin(), outList.end(), outputIter); // print all strings in outList
    cout << endl;

    // reverse iterator
    for (auto iter = outList.rbegin(); iter != outList.rend(); iter ++) // ++ of reverse iterator will move forward
    {
        cout << *iter << " ";
    }
    cout << endl;
    // reverse iterator to normal iterator
    auto overIter = find(outList.crbegin(), outList.crend(), "over");
    printElements(outList.crbegin(), overIter); // result is in reverse order: back dog's lazy the
    printElements(overIter.base(), outList.cend()); // result: the lazy dog's back

    return 0;
}