//
// algorithms.h
// Header file for algorithms functions
//

#ifndef ALGORITHMS_H
#define ALGORITHMS_H


#include <iostream>
#include "api.h"


//namespace for sorting algorithms
namespace SORTING {


/*
 * Sorts vector, which is passed in
 * Parameters:
 * --v: vector of ints, which user has entered
 * Returns:
 * --a vector, containing vectors, representing changes made in one step(e.g swapping to values would have 2 elements)
 */
std::vector< std::vector<arrayModificationInfo*> > bubbleSort(std::vector<int>& v) {
    std::vector< std::vector<arrayModificationInfo*> > changes = {};
    int n = v.size();

    // Outer loop that corresponds to the number of
    // elements to be sorted
    for (size_t i = 0; i < n - 1; i++) {

        // Last i elements are already
        // in place
        for (size_t j = 0; j < n - i - 1; j++) {

                // Comparing adjacent elements
            if (v[j] > v[j + 1]){
                    // Swapping if in the wrong order
                std::swap(v[j], v[j + 1]);
                std::vector<arrayModificationInfo*> stepChanges = { //vector of changes for every step for simultaneous animations
                    new arrayModificationInfo{
                        j, j+1
                    },
                    new arrayModificationInfo{
                        j+1, j
                    }
                };

                changes.push_back(stepChanges);
            }
        }
    }

    return changes;
}



} //SORTING



namespace SEARCH{

}// SEARCH

#endif //ALGORITHMS_H
