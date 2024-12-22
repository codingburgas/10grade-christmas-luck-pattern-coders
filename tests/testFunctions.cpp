#include "testFunctions.h"

#include <iostream>
#include <string>

//files, which are tested
#include "word.h"
#include "scrapping/parser.h"
#include "fileManager.h"
#include "wordAlgorithms.h"


/*
 * Executes all tests in the program and reports the results
 * Parameters:
 * -- None
 * Returns:
 * -- int: 0 if all tests pass, 1 if any test fails
 */
int test(){
    bool failed = false;


    {
        std::cout << "----Testing getTagData-----------\n";
        int code = test_getTagData();
        printResult(code, &failed);

        std::cout << "---------------------------------\n";
    }



    {
        std::cout << "----Testing select-----------\n";
        int code = test_select();
        printResult(code, &failed);

        std::cout << "---------------------------------\n";
    }





    {
        std::cout << "----Testing sortWords-----------\n";
        int code = test_sortWords();
        printResult(code, &failed);

        std::cout << "---------------------------------\n";
    }




    {
        std::cout << "----Testing leaveWordsWithSpecificPart-----------\n";
        int code = test_leaveWordsWithSpecificPart();
        printResult(code, &failed);

        std::cout << "---------------------------------\n";
    }



    {
        std::cout << "----Testing countSyllables-----------\n";
        int code = test_countSyllables();
        printResult(code, &failed);

        std::cout << "---------------------------------\n";
    }


    if (failed){
        std::cout << "\n\nProgram works not as intended\n\n";
    } else{
        std::cout << "\n\nProgram is ready to run\n\n";
    }

    return (int)(failed);
}


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
        std::cerr << "Unexpected exit code\n";
        *failed = true;
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
 * Tests the getTagData function
 * Parameters:
 * -- None
 * Returns:
 * -- int: 0 if all tests pass, 1 if any test fails
 */
int test_getTagData(){
    int code = 0;

    std::vector<std::string> testTags = {
        "<a class=\"testLink\" href=\"someUrl\">Click to change page</a>",
        "<div class=\"info\">Information</div>"
    };

    std::vector<Tag> expectedTags = {
        Tag{
            .properties = {
                {"outerHTML", "<a class=\"testLink\" href=\"someUrl\">Click to change page</a>"},
                {"visibleText", "Click to change page"},
                {"class", "testLink"},
                {"href", "someUrl"}
            }
        },
        Tag{
            .properties = {
                {"outerHTML", "<div class=\"info\">Information</div>"},
                {"visibleText", "Information"},
                {"class", "info"},
            }
        },
    };

    for (size_t i=0; i<testTags.size(); i++){
        size_t tagPosition = 0;
        Tag tag = getTagData(testTags[i], tagPosition);

        if (tag != expectedTags[i]) code = 1;
    }

    return code;
}



/*
 * Tests the select function
 * Parameters:
 * -- None
 * Returns:
 * -- int: 0 if all tests pass, 1 if any test fails
 */
int test_select(){
    int code = 0;

    std::vector< std::pair<std::string, std::string> > testData = {
        {"<a class=\"query\" href=\"some_url\">Click</a><a class=\"query\" href=\"some_url\">Click</a>", "<a class=\"query\""},
        {"<div id=\"div_id\">some info</div>", "<div id=\"div_id\""}
    };

    std::vector<int> expectedLength = {2, 1};

    for (size_t i=0; i<testData.size(); i++){
        if (select(testData[i].first, testData[i].second).size() != expectedLength[i]) code = 1;
    }

    return code;
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
        {new Word{ .word = "apple"}, new Word{ .word = "banana"}, new Word{ .word = "apples" }, new Word{ .word = "orange"}},
        {new Word{ .word = "d"}, new Word{ .word = "c"}, new Word{ .word = "b"}, new Word{ .word = "a"}},
        {new Word{ .word = "apple", .difficulty = "c1"}, new Word{ .word = "banana", .difficulty = "b1"}, new Word{ .word = "apples", .difficulty = "a1"}, new Word{ .word = "orange", .difficulty = "a2"}},
    };


    std::vector<std::string> propertyToSortBy = {"word", "word", "difficulty"};

    std::vector< std::vector< Word* > > expectedResults{
        {new Word{ .word = "apple"}, new Word{ .word = "apples"}, new Word{ .word = "banana"}, new Word{ .word = "orange"}},
        {new Word{ .word = "a"}, new Word{ .word = "b"}, new Word{ .word = "c"}, new Word{ .word = "d"}},
        {new Word{ .word = "apples", .difficulty = "a1"}, new Word{ .word = "orange", .difficulty = "a2"}, new Word{ .word = "banana", .difficulty = "b1"}, new Word{ .word = "apple", .difficulty = "c1"} }
    };


    for (size_t i=0; i<testArrays.size(); i++){
        sortWords( testArrays[i], propertyToSortBy[i] );
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



/*
 * Tests the countSyllables function
 * Parameters:
 * -- None
 * Returns:
 * -- int: 0 if all tests pass, 1 if any test fails
 */
int test_countSyllables(){
    int code = 0;

    std::vector<std::string> testWords = {
        "count", "ally", "Bulgaria", "programming"
    };

    std::vector<int> expectedSyllablesCount = {
        1, 2, 4, 3
    };

    for (size_t index=0; index<testWords.size(); index++){
        int syllablesCount = countSyllables(testWords[index]);
        if (syllablesCount != expectedSyllablesCount[index]) code = 1;
        if (code == 1){
            std::cout << "Word is " << testWords[index] << " and program returned " << syllablesCount << "\n";
        }
    }

    return code;
}
