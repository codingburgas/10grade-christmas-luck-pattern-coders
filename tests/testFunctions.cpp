
#include "testFunctions.h"

#include <iostream>
#include <string>

//files, which are tested
#include "scrapping/parser.h"
#include "fileManager.h"
#include "wordAlgorithms.h"


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


/*void test_getTagData(){
    std::string htmlCode = "<h1>This is for test</h1><a class=\"some class\" href=\"some/url\">Some text</a>";
    //std::string selector = "<a class=\"some class\"";
    size_t tagPos = 25;

    Tag *tag = getTagData(htmlCode, tagPos);
    for (size_t i=0; i<tag->properties.size(); i++){
        std::cout << tag->properties[i][0] << ": " << tag->properties[i][1] << "\n";
    }
}




void test_select(){
    std::string htmlCode = "<h1>This is for test</h1><a class=\"some class\" href=\"some/url\" type=\"Button\">Some text</a><h1>This is for test</h1><a class=\"some class\" href=\"some/url\">Some text</a>";
    std::string selector = "<a class=\"some class\"";


    std::vector<Tag*> tags = select(htmlCode, selector);
    for (auto *tag:tags){
        std::cout << "------------------\n";
        for (size_t i=0; i<tag->properties.size(); i++){
            std::cout << tag->properties[i][0] << ": " << tag->properties[i][1] << "\n";
        }
        std::cout << "------------------\n";
    }

}*/


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


int test_sortWords(){
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
            return 1;
        }
    }

    return 0;
}



int test_leaveWordsWithSpecificPart(){
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
            return 1;
        }
    }



    return 0;


}
