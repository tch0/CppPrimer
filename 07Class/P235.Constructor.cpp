#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student
{
public:
    // constructor
    Student() = default;
    unsigned int getId() const {return id;}
    string getName() const {return name;}
    unsigned int getAge() const {return age;}
    double getCredit() const {return credit;}
private:
    unsigned int id;
    string name;
    unsigned int age;
    double credit;
    vector<string> friends;
};

class Test
{
public:
    const Student& s = Student();
};

ostream& operator<<(ostream& os, const Student& s)
{
    cout << s.getId() << " : " << s.getName() << " " << s.getAge() << " " << s.getCredit() << endl;
    return os;
}

int main(int argc, char const *argv[])
{
    Student s; // using synthesized default constructor, members will be random values
    cout << s;

    cout << sizeof(Test) << endl; // 8
    return 0;
}
