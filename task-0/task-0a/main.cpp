#include "module1.h"
#include "module2.h"

#include <iostream>

using std::cout;
int main(int argc, char** argv)
{
    cout <<  "Hello world!" << "\n";
    cout << Module1::getMyName() << "\n";
    cout << Module2::getMyName() << "\n";

    using namespace Module1;
    cout << getMyName() << "\n"; // (A)
    cout << Module2::getMyName() << "\n";

    //using namespace Module2; // (B)
    //std::cout << getMyName() << "\n"; // COMPILATION ERROR (C)

    using Module2::getMyName;
    cout << getMyName() << "\n"; // (D)
}

