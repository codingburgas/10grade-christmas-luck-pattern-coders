//
// test.cpp
// C++ file for testing program
//

#include <iostream>

#include "testFunctions.h"



int main(int argc, char *argv[]){

    int code;

    {
        std::cout << "----------------------\nTesting 'userInputToVector'\n\n";
        code = test_userInputToVector();

        switch (code) {
            case 0: {
                std::cout << "All tests passed\n";
                break;
            }
            default: {
                std::cerr << "One of the tests failed\n";
                break;
            }
        }

        std::cout << "\n\n------------------------";
    }


    {
        std::cout << "----------------------\nTesting 'performAlgorithm'\n\n";
        code = test_performAlgorithm(argc, argv);

        switch (code) {
        case 0: {
            std::cout << "All tests passed\n";
            break;
        }
        default: {
            std::cerr << "One of the tests failed\n";
            break;
        }
        }

        std::cout << "\n\n------------------------";
    }


    return 0;
}
