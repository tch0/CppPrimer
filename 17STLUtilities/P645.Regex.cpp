#include <iostream>
#include <string>
#include <regex>
#include <iterator>
using namespace std;

// check if phone number is valid
// R"##((\()?(\d{3})(\))?([-.])?(\d{3})([-.]?)(\d{4}))##" -> 7 subexpressions
//        1     2     3     4       5     6     7
bool phoneValid(const smatch& m)
{
    // check ssub_match in m
    // begin with a (
    if (m[1].matched)
    {
        return m[3].matched && (m[4].matched == 0 || m[4].str() == " ");
    }
    // no ) and the delimiters must match.
    else
    {
        return !m[3].matched && m[4].str() == m[6].str();
    }
}

int main(int argc, char const *argv[])
{
    string pattern("[^c]ei"); // pattern ei but not cei
    pattern = "[a-zA-Z]*" + pattern + "[a-zA-Z]*"; // why [:aplha:] is an invalid character class.
    regex r(pattern);
    smatch results; // match the type of regex : string -> smatch, const char* -> cmatch
    string testStr = "receipt their theif receive";
    if (regex_search(testStr, results, r))
    {
        cout << results.str() << endl; // theif
    }
    cout << "smatch size: " << results.size() << endl;
    cout << regex_match("theif", r) << endl; // match the whole string
    cout << endl;

    // regex_iterator s/c/ws/w
    // construct and ++it will call regex_search
    for (sregex_iterator it(testStr.begin(), testStr.end(), r), end_it; it != end_it; ++it)
    {
        // output context of thematching substring
        auto pos = it->prefix().length();
        pos = pos > 40 ? pos - 40 : 0; // print at most 40 chars for context both sides
        cout << it->prefix().str().substr(pos)
             << "\n\t >>> " << it->str() << "<<<\n"
             << it->suffix().str().substr(0, 40)
             << endl;
    }
    cout << endl;

    // subexpression
    // raw string literal : "(contents)"
    regex r2(R"(([a-zA-Z0-9]+)\.(cpp|cxx|cc))"); // subexp1: ([a-zA-Z0-9]+), subexp2: (cpp|cxx|cc)
    string filename = R"(D:\Models\SukaSuka\Nephren.cpp)";
    if (regex_search(filename, results, r2))
    {
        cout << "0: " << results.str(0) << ",\tpos: " << results.position(0) << endl;
        cout << "1: " << results.str(1) << ",\tpos: " << results.position(1) << endl;
        cout << "2: " << results.str(2) << ",\t\tpos: " << results.position(2) << endl;
        // traverse subexpressions
        // first subexpression is match of the whole pattern, then will be the matches of subexpressions
        for (auto it = results.begin(); it != results.end(); ++it)
        {
            cout << it->str() << ", len: " << it->length() << endl;
        }
    }
    cout << endl;

    // using regex for data verification
    // the phone number of America
    // (xxx)-xxx-xxxx
    string phone = R"##((\()?(\d{3})(\))?([-.])?(\d{3})([-.]?)(\d{4}))##"; // 7 subexpressions
    //                    1     2     3     4       5     6     7
    regex rphone(phone);
    smatch m;
    string s;
    while (getline(cin, s))
    {
        for (sregex_iterator it(s.begin(), s.end(), rphone), end_it; it != end_it; ++it)
        {
            if (phoneValid(*it))
            {
                cout << "valid: " << it->str() << endl;
                // regex_replace: replace subexpression
                // format string: use $num represent the num-th subexpression
                cout << "format to ddd.ddd.dddd: " << regex_replace(it->str(), rphone, "$2.$5.$7") << endl;
                // equal to:
                string replaceResult;
                it->format(back_inserter(replaceResult), string("$2.$5.$7")); // why need explicitly construct fmt to a std::string.
                cout << "format to ddd.ddd.dddd2: " << replaceResult << endl;
                // also equals to : 
                cout << "format to ddd.ddd.dddd3: " << it->format("$2.$5.$7") << endl;
            }
            else
            {
                cout << "invalid: " << it->str() << endl;
            }
        }
        // if not match, means not a phone number, will be no output
    }
    return 0;
}
