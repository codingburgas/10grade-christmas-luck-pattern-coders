//
// wordAlgorithms.h
// Header file, which performs operations with array of 'Word's
//

#ifndef WORDALGORITHMS_H
#define WORDALGORITHMS_H


#include <iostream>
#include <vector>
#include "word.h"



/*
 * insertion sort for array of words
 * Parameters:
 * --arr: array of words
 * --begin: starting index of the subarray to partition
 * --end: ending index of the subarray to partition
 * Returns:
 * --None
 */
void insertionSort(std::vector<Word*>& arr, int begin, int end);


/*
 * Partition function for quicksort on an array of words
 * Parameters:
 * --arr: array of Word objects to partition
 * --begin: starting index of the subarray to partition
 * --end: ending index of the subarray to partition
 * Returns:
 * --The index of the pivot element after partitioning
 */
int partition(std::vector<Word*>& arr, int begin, int end);


/*
 * quick sort for array of words
 * Parameters:
 * --arr: array of words
 * --begin: starting index of the subarray to partition
 * --end: ending index of the subarray to partition
 * Returns:
 * --None
 */
void quickSort(std::vector<Word*>& arr, int begin, int end);


/*
 * Hybrid sort for array of words
 * Parameters:
 * --arr: array of words
 * --begin: index, from which to start sorting
 * --end: index, where to end sorting
 * Returns:
 * --None
 */
void hybridSort(std::vector<Word*>& arr, int begin, int end);


/*
 * sorts array of words by alphabet
 * Parameters:
 * --arr: array of words
 * Returns:
 * --None
 */
void sortWords(std::vector<Word*>& arr);


/*
 * Removes words from the vector where the specified property contains a specific part.
 * Parameters:
 * --arr: The vector of Word pointers to filter.
 * --part: The part of the string to search for within the specified property.
 * --propertyName: The name of the property to search for the part.
 * --caseSensitive: A boolean flag to determine if the search should be case-sensitive.
 */
void leaveWordsWithSpecificPart(std::vector<Word*>& arr, std::string& part, std::string& propertyName, bool& caseSensitive);



#endif // WORDALGORITHMS_H
