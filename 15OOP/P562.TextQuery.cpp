#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <memory>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
using namespace std;

// auxiliary functions
// string to lower case
string strToLower(string str)
{
    for_each(str.begin(), str.end(), [](char& c) -> void { c = tolower(c); });
    return str;
}

// Text query program that promote 12DynamicMemory/P430.TextQuery.cpp
// support complex query: 
// 1. match a word : alice
// 2. not match a word : ~(alice)
// 3. or : (hair ! alice)
// 4. and: (hair & alice)
// 5. nested conditions: ((hello & hair) | alice)

// OOP design:
// QueryBase
//      |________WordQuery (1)
//      |________NotQuery (2)
//      |________BinaryQuery (3,4)
//                  |_______OrQuery (3)
//                  |_______AndQuery (4)
// methods:
//  QueryResult eval(TextQuery tq);
//  string rep(); // the query string

// create query command:
//      ((hello & hair) | alice) will be run like:
//      Query q = Query("hello") & Query("hair") | Query("alice");
// use Query class as a interface class, save a QueryBase pointer.
// overload all operators (&|~), generate a new Query object that bind to AndQuery/OrQuery/NotQuery.

// Query q = Query("hello") & Query("hair") | Query("alice") will be like:
//      Query --> OrQuery ----> AndQuery ----------> WordQuery (hello)
//         q        |               |______________> WordQuery (hair)
//                  |_________> WordQuery (alice)


using LineNumber = vector<string>::size_type;

// save query result
class QueryResult
{
    friend ostream& operator<<(ostream& os, const QueryResult& res);
public:
    QueryResult(const string& s, shared_ptr<set<LineNumber>> p, shared_ptr<vector<string>> f)
        : word(s), lines(p), file(f) {}
    // added functions
    shared_ptr<vector<string>> getFile() const { return file; }
    set<LineNumber>::iterator begin() { return lines->begin(); }
    set<LineNumber>::iterator end() { return lines->end(); }
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
            // to lower case, ignore case when query
            word = strToLower(word);
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

QueryResult TextQuery::query(const string& word) const
{
    // if word is not found, will return this empty set
    static shared_ptr<set<LineNumber>> nodata(new set<LineNumber>);
    auto loc = wordmap.find(strToLower(word)); // ignore cases for query
    if (loc != wordmap.end()) // found
    {
        return QueryResult(word, loc->second, file);
    }
    else // not found
    {
        return QueryResult(word, nodata, file);
    }
}

// query
class QueryBase
{
    friend class Query;
protected:
    virtual ~QueryBase() = default;
private:
    virtual QueryResult eval(const TextQuery&) const = 0;
    virtual string rep() const = 0; // the query string
};

// interface calss, point to QueryBase
class Query
{
    friend Query operator~(const Query&);
    friend Query operator|(const Query&, const Query&);
    friend Query operator&(const Query&, const Query&);
public:
    Query(const string& word); // construct a new WordQuery
    QueryResult eval(const TextQuery& tq) const
    {
        return q->eval(tq);
    }
    string rep() const
    {
        return q->rep();
    }
private:
    Query(shared_ptr<QueryBase> query) : q(query) {} // copy constructor
private:
    shared_ptr<QueryBase> q;
};

// output operator of Query object
ostream& operator<<(ostream& os, const Query& query)
{
    return os << query.rep();
}

// derived classes of QueryBase
class WordQuery : public QueryBase
{
    friend class Query; // only for Query, all private
private:
    WordQuery(const string& s) : queryWord(s) {}
    QueryResult eval(const TextQuery& tq) const override
    {
        return tq.query(queryWord);
    }
    string rep() const override
    {
        return queryWord;
    }
private:
    string queryWord;
};

Query::Query(const string& word) : q(new WordQuery(word))
{

}

class NotQuery : public QueryBase
{
    friend Query operator~(const Query& operand);
private:
    NotQuery(const Query& q) : query(q) {}
    QueryResult eval(const TextQuery& tq) const override;
    string rep() const override
    {
        return "~(" + query.rep() + ")";
    }
private:
    Query query;
};

// ~ operator
inline Query operator~(const Query& operand)
{
    return shared_ptr<QueryBase>(new NotQuery(operand));
}

// & and |
class BinaryQuery : public QueryBase
{
protected:
    BinaryQuery(const Query& l, const Query& r, string s) : lhs(l), rhs(r), opSym(s) {}
    string rep() const override
    {
        return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")";
    }
protected:
    Query lhs, rhs;
    string opSym;   // the name of operator
};

class AndQuery : public BinaryQuery
{
    friend Query operator&(const Query&, const Query&);
private:
    AndQuery(const Query& left, const Query& right) : BinaryQuery(left, right, "&") {}
    QueryResult eval(const TextQuery& tq) const override;
};

// & operator
inline Query operator&(const Query& lhs, const Query& rhs)
{
    return shared_ptr<QueryBase>(new AndQuery(lhs, rhs));
}

class OrQuery : public BinaryQuery
{
    friend Query operator|(const Query&, const Query&);
private:
    OrQuery(const Query& left, const Query& right) : BinaryQuery(left, right, "|") {}
    QueryResult eval(const TextQuery& tq) const override;
};

// | operator
inline Query operator|(const Query& lhs, const Query& rhs)
{
    return shared_ptr<QueryBase>(new OrQuery(lhs, rhs));
}

// function eval implementation
QueryResult NotQuery::eval(const TextQuery& tq) const
{
    QueryResult result = query.eval(tq);
    auto retLines = make_shared<set<LineNumber>>();
    // auto beg = result.begin(), end = result.end();
    // auto sz = result.getFile()->size();
    // for (size_t n = 0; n < sz; ++n)
    // {
    //     if (beg == end || *beg != n)
    //     {
    //         retLines->insert(n);
    //     }
    //     else // begin != end && *begin == n
    //     {
    //         ++beg;
    //     }
    // }
    vector<LineNumber> vec(result.getFile()->size(), 0);
    for (size_t i = 0; i < vec.size(); ++i)
    {
        vec[i] = i;
    }
    set_difference(vec.begin(), vec.end(), result.begin(), result.end(), 
        inserter(*retLines, retLines->begin()));
    return QueryResult(rep(), retLines, result.getFile());
}

// the union of two sets
QueryResult OrQuery::eval(const TextQuery& tq) const
{
    QueryResult left = lhs.eval(tq);
    QueryResult right = rhs.eval(tq);
    auto retLines = make_shared<set<LineNumber>>(left.begin(), left.end());
    retLines->insert(right.begin(), right.end());
    return QueryResult(rep(), retLines, left.getFile());
}

// intersection of two sets
QueryResult AndQuery::eval(const TextQuery& tq) const
{
    QueryResult left = lhs.eval(tq);
    QueryResult right = rhs.eval(tq);
    auto retLines = make_shared<set<LineNumber>>();
    set_intersection(left.begin(), left.end(), right.begin(), right.end(),
        inserter(*retLines, retLines->begin())); // insert reuslt to retLines
    return QueryResult(rep(), retLines, left.getFile());
}

// output result
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
    // runQueries(fin);
    TextQuery tq(fin);
    Query q = (Query("he") | Query("she")) & Query("is") & ~Query("the");
    cout << q.eval(tq);
    return 0;
}
