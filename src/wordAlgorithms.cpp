
#include "wordAlgorithms.h"

#include <iostream>
#include <vector>
#include <string>

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
void insertionSort(std::vector<Word>& arr, int begin, int end) {
    for (int i = begin + 1; i <= end; ++i) {
        Word key = arr[i];
        int j = i - 1;

        // Compare strings lexicographically
        while (j >= begin && arr[j].word > key.word) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

/*
 * Partition function for quicksort on an array of words
 * Parameters:
 * --arr: array of Word objects to partition
 * --begin: starting index of the subarray to partition
 * --end: ending index of the subarray to partition
 * Returns:
 * --The index of the pivot element after partitioning
 */

int partition(std::vector<Word>& arr, int begin, int end) {
    std::string pivot = arr[end].word;
    int i = begin - 1;

    for (int j = begin; j < end; ++j) {
        if (arr[j].word <= pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[end]);
    return i + 1;
}

/*
 * quick sort for array of words
 * Parameters:
 * --arr: array of words
 * --begin: starting index of the subarray to partition
 * --end: ending index of the subarray to partition
 * Returns:
 * --None
 */
void quickSort(std::vector<Word>& arr, int begin, int end) {
    if (begin < end) {
        int pivotIndex = partition(arr, begin, end);
        quickSort(arr, begin, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, end);
    }
}

/*
 * Hybrid sort for array of words
 * Parameters:
 * --arr: array of words
 * --begin: index, from which to start sorting
 * --end: index, where to end sorting
 * Returns:
 * --None
 */
void hybridSort(std::vector<Word>& arr, int begin, int end) {
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
 * sorts array of words by alphabet
 * Parameters:
 * --arr: array of words
 * Returns:
 * --None
 */
void sortWords(std::vector<Word>& arr) {
    if (!arr.empty()) {
        hybridSort(arr, 0, arr.size() - 1);
    }
}

