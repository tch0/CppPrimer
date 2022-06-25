#include <exception>
#include <stdexcept>
#include <new> // for bad_alloc
#include <typeinfo> // for bad_cast
#include <iostream>
using namespace std;

// terminate mechanism
// when an expetion thrown but not been catched, call std::terminate
// call set_terminate to customize the behaviour

void handler()
{
    cout << "called handler() when expection thrown!" << endl;
}

int main(int argc, char const *argv[])
{
    set_terminate(handler);
    try
    {
        throw bad_alloc();
    }
    catch (logic_error& e)
    {
        cout << "logic error : " << e.what() << endl;
    }
    catch (runtime_error& e)
    {
        cout << "runtime error : " << e.what() << endl;
    }
    return 0;
}
