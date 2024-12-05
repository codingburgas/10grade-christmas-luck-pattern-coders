//
// test.cpp
// C++ file for testing program
//

//#include <iostream>

#include "testFunctions.h"



int main(){
    int code = test_userInputToVector();

    switch (code) {
        case 0: {
            std::cout << "All tests passed";
            break;
        }
        default: {
            std::cerr << "One of the tests failed";
            break;
        }
    }

    return code;
}