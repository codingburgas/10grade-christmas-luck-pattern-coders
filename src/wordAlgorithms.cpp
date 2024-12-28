//
// wordAlgorithms.cpp
// C++ file, which performs operations with array of 'Word's
//

#include "wordAlgorithms.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // For std::remove
#include <cctype>    // For std::tolower

#include "word.h"


/* Reverses vector
 * Parameters:
 * --v: vector
 * Returns:
 * --None
 */
template<typename T>
void reverseVector(std::vector<T>& v){
    std::reverse(v.begin(), v.end());
}

/*
 * Converts all characters in the given string to lowercase.
 * Parameters:
 * --str: The string to convert to lowercase.
 * Returns:
 * --std::string: The converted lowercase string.
 */
std::string toLower(std::string str) {
    for (auto& c : str) {
        c = tolower(c);
    }
    return str;
}



/*
 * Insertion sort for array of word pointers
 * Parameters:
 * --arr: array of word pointers
 * --propertyName: string, which contains property to sort by
 * --begin: starting index of the subarray to partition
 * --end: ending index of the subarray to partition
 * Returns:
 * --None
 */
void insertionSort(std::vector<Word*>& arr, std::string &propertyName, int begin, int end) {
    for (int i = begin + 1; i <= end; ++i) {
        Word* key = arr[i];
        int j = i - 1;

        if (propertyName == "frequencyOfUse"){
            // compare words' frequency as ints, not strings
            while (j >= begin && arr[j]->frequencyOfUse > key->frequencyOfUse) {
                arr[j + 1] = arr[j];
                --j;
            }
        } else{
            std::string keyProperty = toLower(key->getProperty(propertyName));
            while (j >= begin && toLower(arr[j]->getProperty(propertyName)) > keyProperty) {
                arr[j + 1] = arr[j];
                --j;
            }
        }

        arr[j + 1] = key;
    }
}

/*
 * Partition function for quicksort on an array of word pointers
 * Parameters:
 * --arr: array of word pointers to partition
 * --propertyName: string, which contains property to sort by
 * --begin: starting index of the subarray to partition
 * --end: ending index of the subarray to partition
 * Returns:
 * --The index of the pivot element after partitioning
 */
int partition(std::vector<Word*>& arr, std::string &propertyName, int begin, int end) {
    if (propertyName == "frequencyOfUse"){
        unsigned long pivot = arr[end]->frequencyOfUse;

        int i = begin - 1;

        for (int j = begin; j < end; ++j) {
            // compare words' frequency as ints, not strings
            if (arr[j]->frequencyOfUse <= pivot) {
                ++i;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[end]);
        return i + 1;


    } else{
        std::string pivot = toLower(arr[end]->getProperty(propertyName));

        int i = begin - 1;

        for (int j = begin; j < end; ++j) {
            if (toLower(arr[j]->getProperty(propertyName)) <= pivot) {
                ++i;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[end]);
        return i + 1;
    }


}


/*
 * Quicksort for array of word pointers
 * Parameters:
 * --arr: array of word pointers
 * --propertyName: string, which contains property to sort by
 * --begin: starting index of the subarray to partition
 * --end: ending index of the subarray to partition
 * Returns:
 * --None

void quickSort(std::vector<Word*>& arr, int begin, int end) {
    if (begin < end) {
        int pivotIndex = partition(arr, begin, end);
        quickSort(arr, begin, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, end);
    }
}
*/

/*
 * Hybrid sort for array of word pointers
 * Parameters:
 * --arr: array of word pointers
 *--propertyName: string, which contains property to sort by
 * --begin: index, from which to start sorting
 * --end: index, where to end sorting
 * Returns:
 * --None
 */
void hybridSort(std::vector<Word*>& arr, std::string &propertyName, int begin, int end) {
    const int SMALL_THRESHOLD = 32;

    if (end - begin + 1 <= SMALL_THRESHOLD) {
        // Use Insertion Sort for small subarrays
        insertionSort(arr, propertyName, begin, end);
    } else {
        // Use Quicksort for larger subarrays
        int pivotIndex = partition(arr, propertyName, begin, end);
        hybridSort(arr, propertyName, begin, pivotIndex - 1);
        hybridSort(arr, propertyName, pivotIndex + 1, end);
    }
}

/*
 * sorts array of words by alphabet
 * Parameters:
 * --arr: array of words
 * --propertyName: string, which contains property to sort by
 * --ascendingOrder: boolean, which represents if vector should be sorted in ascending ot descending order
 * Returns:
 * --None
 */
void sortByProperty(std::vector<Word*>& arr, std::string &propertyName, bool ascendingOrder){
    if (!arr.empty()) {
        hybridSort(arr, propertyName, 0, arr.size() - 1);
        if (!ascendingOrder){
            reverseVector(arr);
        }
    }
}



/*
 * Checks if a string (part) is found within another string (fullString).
 * The case-sensitivity of the search can be controlled by the caseSensitive flag.
 * Parameters:
 * --part: The substring to search for.
 * --fullString: The string in which to search for the part.
 * --caseSensitive: A boolean flag to determine if the search should be case-sensitive.
 * Returns:
 * --size_t: Returns index of part wihin fullString
 */
size_t findIndex(std::string& part, std::string& fullString, bool& caseSensitive) {
    if (caseSensitive) {
        return fullString.find(part);
    } else {
        return toLower(fullString).find(toLower(part));
    }
}

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
void leaveWordsWithSpecificPart(std::vector<Word*>& arr, std::string& part, std::string& propertyName, bool caseSensitive, bool startsWith, bool endsWith) {
    for (auto it = arr.begin(); it != arr.end(); ) {
        std::string wordProperty = (*it)->getProperty(propertyName);
        bool erased = false;

        size_t index = findIndex(part, wordProperty, caseSensitive);
        if ((index == std::string::npos) || (startsWith && index != 0) || (endsWith && index != (wordProperty.size() - part.size()))){
            it = arr.erase(it);
            erased = true;
        }


        if (!erased){
            it++;
        }

    }
}




/*
 * Erases all words, which don't have any of specified tags
 * Parameters:
 * --arr: vector of words
 * --tags: vector of tags
 * Returns:
 * --None
 */
void leaveWordsWithSpecificTags(std::vector<Word*>& arr, std::vector<std::string>& tags){
    for (size_t i=0; i<arr.size(); i++){
        bool containsTag = false;
        for (std::string& tag : tags){
            if (contains(arr[i]->tags, tag)){
                containsTag = true;
                break;
            }
        }

        if (!containsTag){
            arr.erase(arr.begin() + i);
        }
    }
}

