#include <iostream>
#include <string>
using namespace std;

// usually use anonymous union, with a discriminant to identify the type that union save
class Token
{
    friend ostream& operator<<(ostream& os, const Token& t);
public:
    Token() : tok(INT), ival(0) {}
    Token(const Token& t) : tok(t.tok)
    {
        copyUnion(t);
    }
    Token& operator=(const Token& t);
    ~Token()
    {
        if (tok == STR)
        {
            sval.~string();
        }
    }
    Token& operator=(char c);
    Token& operator=(int i);
    Token& operator=(double d);
    Token& operator=(const string& s);
private:
    enum {INT, CHAR, DBL, STR} tok;
    union // anonymous union
    {
        char cval;
        int ival;
        double dval;
        string sval;
    };
    void copyUnion(const Token& t);
};
Token& Token::operator=(char c)
{
    if (tok == STR)
        sval.~string();
    cval = c;
    tok = CHAR;
    return *this;
}

Token& Token::operator=(int i)
{
    if (tok == STR)
        sval.~string();
    ival = i;
    tok = INT;
    return *this;
}

Token& Token::operator=(double d)
{
    if (tok == STR)
        sval.~string();
    dval = d;
    tok = DBL;
    return *this;
}

Token& Token::operator=(const string& s)
{
    if (tok == STR)
        sval = s;
    else
        new (&sval) string(s);
    tok = STR;
    return *this;
}

Token& Token::operator=(const Token& t)
{
    if (tok == STR && t.tok != STR)
        sval.~string();
    if (tok == STR && t.tok == STR)
        sval = t.sval;
    else
        copyUnion(t);
    tok = t.tok;
    return *this;
}

void Token::copyUnion(const Token& t)
{
    switch(t.tok)
    {
        case CHAR: cval = t.cval; break;
        case INT: ival = t.ival; break;
        case DBL: dval = t.dval; break;
        case STR: new (&sval) string(t.sval); break;
    }
}

ostream& operator<<(ostream& os, const Token& t)
{
    switch(t.tok)
    {
        case Token::CHAR: os << "char: " << t.cval; break;
        case Token::INT: os << "int: " << t.ival; break;
        case Token::DBL: os << "double: " << t.dval; break;
        case Token::STR: os << "string: " << t.sval; break;
    }
    return os;
}

int main(int argc, char const *argv[])
{
    Token t;
    cout << t << endl;
    t = "hello";
    Token t2 = t;
    cout << t2 << endl;
    return 0;
}
