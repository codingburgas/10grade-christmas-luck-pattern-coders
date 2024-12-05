//
// testing.h
// Header file, where are declared functions, needed for testing
//

#ifndef TESTING_H
#define TESTING_H

#include <iostream>
#include <vector>
#include <string>




/*
 * Converts user input to vector of ints
 * Parameters:
 * --std::vector<T> &vector1: reference to a vector, containing some values
 * --std::vector<T> &vector2: reference to a vector, containing some values
 * Returns:
 * --code: 0 - success
*         -1 - fail
 */
template <typename T>
int compare(std::vector<T> &vector1, std::vector<T> &vector2) {
    // check size of vectors
    if (vector1.size() != vector2.size()) {
        std::cerr << "Vectors have wrong size\n";
        return -1;
    };

    for (int i = 0; i < vector1.size(); i++){
        if (vector1[i] != vector2[i]) {
            std::cerr << "Vectors have different elements on index " << i << ": " << vector1[i] << vector2[i] << "\n";
            return -1;
        };
    }

    return 0;
}

#endif //TESTING_H
