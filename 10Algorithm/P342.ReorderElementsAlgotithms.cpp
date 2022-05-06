#include <vector>
#include <array>
#include <deque>
#include <list>
#include <string>
#include <numeric>
#include <algorithm>
#include <iostream>
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

template<typename ArrOrContainer>
void printAllElements(const ArrOrContainer& container)
{
    printElements(begin(container), end(container));
}

int main(int argc, char const *argv[])
{
    // sort
    vector<string> words{"the", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog's", "back"};
    vector<string> wordsCopy = words;
    sort(wordsCopy.begin(), wordsCopy.end()); // use < of string
    printAllElements(wordsCopy);

    // copy version of sort
    deque<string> wordsResult(words.size());
    partial_sort_copy(words.begin(), words.end(), wordsResult.begin(), wordsResult.end());
    printAllElements(wordsResult);

    // unique
    auto end_unique = unique(wordsResult.begin(), wordsResult.end());
    wordsResult.erase(end_unique, wordsResult.end());
    printAllElements(wordsResult);

    return 0;
}
