
#include "testFunctions.h"

#include <iostream>
#include <string>

//files, which are tested
#include "scrapping/parser.h"
#include "fileManager.h"
#include "wordAlgorithms.h"


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



void test_getJsonDataFromFile(){
    std::string fileName = "../tests/testJsonFile.json";
    json result = getJsonDataFromFile(fileName);

    std::cout << result.dump();
}



void test_sortWords(){
    std::vector<Word> testWords = {
        Word{"apple"}, Word{"banana"}, Word{"apples"}, Word{"orange"}
    };

    for (auto word:testWords) std::cout << word.word << ", ";
    std::cout << "\n";
    sortWords(testWords);
    for (auto word:testWords) std::cout << word.word << ", ";
}
