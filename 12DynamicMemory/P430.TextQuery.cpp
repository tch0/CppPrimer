#include <map>
#include <set>
#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

using LineNumber = vector<string>::size_type;

class QueryResult
{
    friend ostream& operator<<(ostream& os, const QueryResult& res);
public:
    QueryResult(const string& s, shared_ptr<set<LineNumber>> p, shared_ptr<vector<string>> f)
        : word(s), lines(p), file(f) {}
private:
    string word;
    shared_ptr<set<LineNumber>> lines;
    shared_ptr<vector<string>> file;
};

// share data with QueryResult class
class TextQuery
{
public:
    TextQuery(ifstream& fin);
    QueryResult query(const string& word) const;
private:
    void stripPunctuations(string& word);
private:
    shared_ptr<vector<string>> file;
    map<string, shared_ptr<set<LineNumber>>> wordmap;
};

TextQuery::TextQuery(ifstream& fin) : file(new vector<string>)
{
    string line;
    while (getline(fin, line))
    {
        file->push_back(line);
        LineNumber n = file->size() - 1;
        istringstream is(line);
        string word;
        while (is >> word)
        {
            // strip punctuations
            stripPunctuations(word);
            if (!word.empty())
            {
                auto & lines = wordmap[word];
                // first time we meet a word, lines will be a empty shared_ptr of set<LineNumber>
                if (!lines)
                {
                    lines.reset(new set<LineNumber>);
                }
                lines->insert(n);
            }
        }
    }
}
QueryResult TextQuery::query(const string& word) const
{
    // if word is not found, will return this empty set
    static shared_ptr<set<LineNumber>> nodata(new set<LineNumber>);
    auto loc = wordmap.find(word);
    if (loc != wordmap.end()) // found
    {
        return QueryResult(word, loc->second, file);
    }
    else // not found
    {
        return QueryResult(word, nodata, file);
    }
}

void TextQuery::stripPunctuations(string& word)
{
    // strip leading and trailing punctuations
    for (auto iter = word.begin(); iter != word.end(); iter ++)
    {
        if (!ispunct(*iter))
        {
            break;
        }
        iter = word.erase(iter);
    }
    reverse(word.begin(), word.end());
    for (auto iter = word.begin(); iter != word.end(); iter ++)
    {
        if (!ispunct(*iter))
        {
            break;
        }
        iter = word.erase(iter);
    }
    reverse(word.begin(), word.end());
}

ostream& operator<<(ostream& os, const QueryResult& qr)
{
    auto occurTimes = qr.lines->size();
    os << "element " << qr.word << " occurs " << occurTimes << (occurTimes > 1 ? " times:" : " time:") << endl;
    for (auto lineNo : *qr.lines)
    {
        os << "\t(line " << lineNo + 1 << ") " << (*qr.file)[lineNo] << endl;
    }
    return os;
}

// run queries, user program
void runQueries(ifstream& infile)
{
    TextQuery tq(infile);
    while (true)
    {
        cout << "enter word to look for, or q to quit: ";
        string s;
        if (!(cin >> s) || s == "q")
        {
            break;
        }
        cout << tq.query(s) << endl;
    }
}

int main(int argc, char const *argv[])
{
    ifstream fin("hamlet.txt");
    runQueries(fin);
    return 0;
}
