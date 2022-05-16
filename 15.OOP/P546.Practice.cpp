#include <iostream>
using namespace std;

class Base
{
public:
    virtual void memfcn(Base& b)
    {
        b = *this;
    }
};

class Pub_Derv : public Base
{
public:
    virtual void memfcn(Base& b) override
    {
        b = *this;
    }
};
class Prot_Derv : protected Base
{
public:
    virtual void memfcn(Base& b) override
    {
        b = *this;
    }
};
class Priv_Derv : private Base
{
public:
    virtual void memfcn(Base& b) override
    {
        b = *this;
    }
};

class Derived_from_Public : public Pub_Derv
{
public:
    virtual void memfcn(Base& b) override
    {
        b = *this;
    }
};
class Derived_from_Protected : public Prot_Derv
{
public:
    virtual void memfcn(Base& b) override
    {
        b = *this;
    }
};
class Derived_from_Private : public Priv_Derv
{
public:
    // virtual void memfcn(Base& b) override // can not access the subobject of Base
    // {
    //     b = *this;
    // }
};

int main(int argc, char const *argv[])
{
    Pub_Derv d1;
    Prot_Derv d2;
    Priv_Derv d3;
    Derived_from_Public dd1;
    Derived_from_Protected dd2;
    Derived_from_Private dd3;
    Base *p;
    p = &d1;
    // p = &d2; // invalid
    // p = &d3; // invalid
    p = &dd1;
    // p = &dd2; // invalid
    // p = &dd3; // invalid
    return 0;
}