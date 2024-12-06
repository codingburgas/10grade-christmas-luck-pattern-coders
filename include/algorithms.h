//
// algorithms.h
// Header file for algorithms functions
//


#pragma once

#ifndef ALGORITHMS_H
#define ALGORITHMS_H


#include <iostream>
#include <vector>
#include "arrayModificationInfo.h"





//namespace for sorting algorithms
namespace SORTING {


/*
 * Sorts vector, which is passed in
 * Parameters:
 * --v: vector of ints, which user has entered
 * Returns:
 * --a vector, containing vectors, representing changes made in one step(e.g swapping to values would have 2 elements)
 */
std::vector< std::vector<arrayModificationInfo*> > bubbleSort(std::vector<int>& v);



} //SORTING



namespace SEARCH{

}// SEARCH

#endif //ALGORITHMS_H
