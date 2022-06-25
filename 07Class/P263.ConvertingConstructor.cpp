#include <iostream>
#include <string>
using namespace std;

class Person
{
public:
    Person(const string& name) // converting constructor
    {
        this->name = name;
        cout << "Call converting constructor Person(const string& name)" << endl;
    }
    Person(const Person& s) : Person(s.name) // copy constructor
    {
        cout << "Call copy constructor!" << endl;
    }
private:
    string name;
    int age = 0;
};

int main(int argc, char const *argv[])
{
    Person kim("Kim"); // kim = "Kim" is not Ok, it could only convert once, using assignment in initialization will be counted as a conversion.
    Person ron = string("Ron"); // only call Person(const string& name)
    Person shego = Person("Shego"); // also only call Person(const string& name), compiler optimization?
    Person shego2 = shego; // call Person(const Person& s)
    return 0;
}
