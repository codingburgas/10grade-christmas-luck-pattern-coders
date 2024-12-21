#include "testFunctions.h"

#include <iostream>
#include <string>

//files, which are tested
#include "scrapping/parser.h"
#include "fileManager.h"
#include "wordAlgorithms.h"

/*
 * Prints the result of test execution
 * Parameters:
 * -- code: exit code of the test
 * -- failed: pointer to a boolean that tracks if any test has failed
 * Returns:
 * -- None
 */
void printResult(int code, bool *failed){
    switch (code){
    case 0:
        std::cout << "All tests passed successfully\n";
        break;

    case 1:
        std::cout << "One or more tests failed\n";
        *failed = true;
        break;

    default:
        std::cout << "Unexpected exit code\n";
        break;
    }
}

/*
 * Deletes objects in a single pointer
 * Parameters:
 * -- object: pointer to the object to delete
 * Returns:
 * -- None
 */
template<typename T>
void deleteObjectsInVector(T &object){
    delete object;
}


/*
 * Deletes objects in a vector within a specified range
 * Parameters:
 * -- arr: vector of objects to delete
 * -- start: start index of the range (default: 0)
 * -- end: end index of the range (default: end of vector)
 * Returns:
 * -- None
 */
template<typename T>
void deleteObjectsInVector(std::vector<T> &arr, size_t start=0, size_t end=std::string::npos){
    if (end == std::string::npos) end = arr.size();

    for (size_t index=start-1; index<end; ){
        index++;
        deleteObjectsInVector( arr[index] );
        arr.erase(arr.begin() + index);
    }
}

/*
 * Compares two vectors for equality
 * Parameters:
 * -- v1: first vector to compare
 * -- v2: second vector to compare
 * -- useValueAtPointer: flag to compare values at pointers instead of pointers themselves
 * Returns:
 * -- bool: true if vectors are equal, false otherwise
 */
template<typename T>
bool compareVectors(std::vector<T> &v1, std::vector<T> &v2, bool useValueAtPointer){
    if (v1.size() != v2.size()){
        return false;
    }

    for (size_t i=0; i<v1.size(); i++){
        if (useValueAtPointer){

            if ( *(v1[i]) != *(v2[i]) ) return false;

        } else{

            if (v1[i] != v2[i]) return false;

        }

    }

    return true;
}

/*
 * Tests the sortWords function by comparing sorted results to expected outputs
 * Parameters:
 * -- None
 * Returns:
 * -- int: 0 if all tests pass, 1 if any test fails
 */
int test_sortWords(){
    int code = 0;

    std::vector< std::vector< Word* > > testArrays = {
        {new Word{"apple"}, new Word{"banana"}, new Word{"apples"}, new Word{"orange"}},
        {new Word{"d"}, new Word{"c"}, new Word{"b"}, new Word{"a"}}
    };

    std::vector< std::vector< Word* > > expectedResults{
        {new Word{"apple"}, new Word{"apples"}, new Word{"banana"}, new Word{"orange"}},
        {new Word{"a"}, new Word{"b"}, new Word{"c"}, new Word{"d"}}
    };

    for (size_t i=0; i<testArrays.size(); i++){
        sortWords( testArrays[i] );
        if (!compareVectors(testArrays[i], expectedResults[i], true)){
            code = 1;
        }
    }

    deleteObjectsInVector(testArrays);
    deleteObjectsInVector(expectedResults);


    return code;
}

/*
 * Tests the leaveWordsWithSpecificPart function by filtering words with specific properties
 * Parameters:
 * -- None
 * Returns:
 * -- int: 0 if all tests pass, 1 if any test fails
 */
int test_leaveWordsWithSpecificPart(){
    int code = 0;

    std::vector< std::vector< Word* > > testArrays = {
        {new Word{"apple"}, new Word{"banana"}, new Word{"apples"}, new Word{"orange"}, new Word{"APPLICATION"}},
        {new Word{"apple"}, new Word{"banana"}, new Word{"apples"}, new Word{"orange"}, new Word{"APPLICATION"}},
        {new Word{"abcdefgh"}, new Word{"ABCDEFGH"}, new Word{"abcde"}, new Word{"fghabcde"}},
        {new Word{"abcdefgh"}, new Word{"ABCDEFGH"}, new Word{"abcde"}, new Word{"fghabcde"}}
    };

    struct Options{
        std::string part;
        std::string propertyName;
        bool caseSensitive;
    };

    std::vector< Options> options = {
        Options{"app", "word", false},
        Options{"app", "word", true},
        Options{"abcdef", "word", false},
        Options{"abcdef", "word", true}
    };

    std::vector< std::vector< Word* > > expectedResults = {
        {new Word{"apple"}, new Word{"apples"}, new Word{"APPLICATION"}},
        {new Word{"apple"}, new Word{"apples"}},
        {new Word{"abcdefgh"}, new Word{"ABCDEFGH"}},
        {new Word{"abcdefgh"}}
    };



    for (size_t i=0; i<testArrays.size(); i++){
        leaveWordsWithSpecificPart(testArrays[i], options[i].part, options[i].propertyName, options[i].caseSensitive);
        if (!compareVectors(testArrays[i], expectedResults[i], true)){
            code = 1;
        }
    }


    deleteObjectsInVector(testArrays);
    deleteObjectsInVector(expectedResults);


    return code;
}
