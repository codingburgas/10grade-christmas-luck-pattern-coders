//
// testFunctions.h
// Header file with functions, which test functions, that are used in the application
//

#ifndef TEST_FUNCTIONS_H
#define TEST_FUNCTIONS_H

#include <iostream>
#include <vector>
#include <string>

#include "../include/backend.h"
#include "testing.h"



/*
 * tests userInputToVector function
 * Parameters:
 * --None
 * Returns:
 * --int: 0 - success
 *       -1 - fail
 */
int test_userInputToVector() {
    std::vector<std::string> testInputs = {
        "12, 23, 34, 56",
        "12",
        "string",
    };

    std::vector< std::vector<int> > expectedResults = {
        {12, 23, 34, 56},
        {12},
        {},
    };

    //check every test input
    for (int caseIndex = 0; caseIndex<testInputs.size(); caseIndex++) {
        std::string testInput = testInputs[caseIndex];

        std::vector<int> result = userInputToVector(testInput);
        std::vector<int> expectedResult = expectedResults[caseIndex];

             //declared in testing.h
        if ( compare(result, expectedResult) == -1 ){
            return -1; // if compare returned -1(means error), return that testing failed
        }

    }




    return 0;
}

#endif //TEST_FUNCTIONS_H
