#include <iostream>
#include <string>
using namespace std;

class Student
{
private:
    class Id
    {
    public:
        Id(int id) {this->id = id;}
        int getId() {return id;}
    private:
        int id;
    };
public:
    Student(int idNum) : id(idNum) {}
    Id getId();
    using AId = Id;
private:
    Id id;
};

Student::Id Student::getId()
{
    return id;
}

int main(int argc, char const *argv[])
{
    Student s(100);
    cout << s.getId().getId() << endl;
    Student::AId id = s.getId();
    return 0;
}