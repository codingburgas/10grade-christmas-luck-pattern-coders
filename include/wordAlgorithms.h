//
// wordAlgorithms.h
// Header file, which performs operations with array of 'Word's
//

#ifndef WORDALGORITHMS_H
#define WORDALGORITHMS_H


#include <iostream>
#include <vector>
#include <algorithm> // for std::reverse
#include "word.h"



/*
 * insertion sort for array of words
 * Parameters:
 * --arr: array of words
 * --propertyName: string, which contains property to sort by
 * --begin: starting index of the subarray to partition
 * --end: ending index of the subarray to partition
 * Returns:
 * --None
 */
void insertionSort(std::vector<Word*>& arr, std::string &propertyName, int begin, int end);


/*
 * Partition function for quicksort on an array of words
 * Parameters:
 * --arr: array of Word objects to partition
 * --propertyName: string, which contains property to sort by
 * --begin: starting index of the subarray to partition
 * --end: ending index of the subarray to partition
 * Returns:
 * --The index of the pivot element after partitioning
 */
int partition(std::vector<Word*>& arr, std::string &propertyName, int begin, int end);


/*
 * quick sort for array of words
 * Parameters:
 * --arr: array of words
 * --propertyName: string, which contains property to sort by
 * --begin: starting index of the subarray to partition
 * --end: ending index of the subarray to partition
 * Returns:
 * --None
 */
//void quickSort(std::vector<Word*>& arr, std::string &propertyName, int begin, int end);


/*
 * Hybrid sort for array of words
 * Parameters:
 * --arr: array of words
 * --propertyName: string, which contains property to sort by
 * --begin: index, from which to start sorting
 * --end: index, where to end sorting
 * Returns:
 * --None
 */
void hybridSort(std::vector<Word*>& arr, std::string &propertyName, int begin, int end);


template<typename T>
void reverseVector(std::vector<T>& v);

/*
 * sorts array of words by alphabet
 * Parameters:
 * --arr: array of words
 * --propertyName: string, which contains property to sort by
 * --ascendingOrder: boolean, which represents if vector should be sorted in ascending ot descending order
 * Returns:
 * --None
 */
void sortByProperty(std::vector<Word*>& arr, std::string &propertyName, bool ascendingOrder);


/*
 * Removes words from the vector where the specified property contains a specific part.
 * Parameters:
 * --arr: The vector of Word pointers to filter.
 * --part: The part of the string to search for within the specified property.
 * --propertyName: The name of the property to search for the part.
 * --caseSensitive: A boolean flag to determine if the search should be case-sensitive.
 * --startsWith: A boolean flag to determine if word should start with part.
 * --endsWith: A boolean flag to determine if word should end with part.
 */
void leaveWordsWithSpecificPart(std::vector<Word*>& arr, std::string& part, std::string& propertyName, bool caseSensitive, bool startsWith=false, bool endsWith=false);



template<typename T>
bool contains(std::vector<T> &v, T &val){
    for (T& el : v){
        if (el == val){
            return true;
        }
    }

    return false;
}



void leaveWordsWithSpecificTags(std::vector<Word*>& arr, std::vector<std::string>& tags);

#endif // WORDALGORITHMS_H
