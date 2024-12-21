#include "wordAlgorithms.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // For std::remove
#include <cctype>    // For std::tolower

#include "word.h"

/*
 * Insertion sort for array of word pointers
 * Parameters:
 * --arr: array of word pointers
 * --begin: starting index of the subarray to partition
 * --end: ending index of the subarray to partition
 * Returns:
 * --None
 */
void insertionSort(std::vector<Word*>& arr, int begin, int end) {
    for (int i = begin + 1; i <= end; ++i) {
        Word* key = arr[i];
        int j = i - 1;

        // Compare strings lexicographically
        while (j >= begin && arr[j]->word > key->word) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

/*
 * Partition function for quicksort on an array of word pointers
 * Parameters:
 * --arr: array of word pointers to partition
 * --begin: starting index of the subarray to partition
 * --end: ending index of the subarray to partition
 * Returns:
 * --The index of the pivot element after partitioning
 */
int partition(std::vector<Word*>& arr, int begin, int end) {
    std::string pivot = arr[end]->word;
    int i = begin - 1;

    for (int j = begin; j < end; ++j) {
        if (arr[j]->word <= pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[end]);
    return i + 1;
}

/*
 * Quicksort for array of word pointers
 * Parameters:
 * --arr: array of word pointers
 * --begin: starting index of the subarray to partition
 * --end: ending index of the subarray to partition
 * Returns:
 * --None
 */
void quickSort(std::vector<Word*>& arr, int begin, int end) {
    if (begin < end) {
        int pivotIndex = partition(arr, begin, end);
        quickSort(arr, begin, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, end);
    }
}

/*
 * Hybrid sort for array of word pointers
 * Parameters:
 * --arr: array of word pointers
 * --begin: index, from which to start sorting
 * --end: index, where to end sorting
 * Returns:
 * --None
 */
void hybridSort(std::vector<Word*>& arr, int begin, int end) {
    const int SMALL_THRESHOLD = 32;

    if (end - begin + 1 <= SMALL_THRESHOLD) {
        // Use Insertion Sort for small subarrays
        insertionSort(arr, begin, end);
    } else {
        // Use Quicksort for larger subarrays
        int pivotIndex = partition(arr, begin, end);
        hybridSort(arr, begin, pivotIndex - 1);
        hybridSort(arr, pivotIndex + 1, end);
    }
}

/*
 * Sorts array of word pointers by alphabet
 * Parameters:
 * --arr: array of word pointers
 * Returns:
 * --None
 */
void sortWords(std::vector<Word*>& arr) {
    if (!arr.empty()) {
        hybridSort(arr, 0, arr.size() - 1);
    }
}

std::string toLower(std::string str) {
    for (auto& c : str) {
        c = tolower(c);
    }
    return str;
}

bool stringContainsAnother(std::string& part, std::string& fullString, bool& caseSensitive) {
    if (caseSensitive) {
        return fullString.find(part) == std::string::npos;
    } else {
        return toLower(fullString).find(toLower(part)) == std::string::npos;
    }
}

void leaveWordsWithSpecificPart(std::vector<Word*>& arr, std::string& part, std::string& propertyName, bool& caseSensitive) {
    for (auto it = arr.begin(); it != arr.end(); ) {
        std::string wordProperty = (*it)->getProperty(propertyName);
        if (stringContainsAnother(part, wordProperty, caseSensitive)) {
            it = arr.erase(it);
        } else {
            ++it;
        }
    }
}
