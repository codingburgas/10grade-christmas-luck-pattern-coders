#include <iostream>
#include <string>
#include <vector>
#include "../include/parser.h"


Tag *getTagData(std::string &htmlCode, size_t &tagPosition){
    //<a href="url">Text</a>
    auto *tag = new Tag{};

    //<a href="url">Text</a>
    //             ↑
    size_t closingBracketPosition = htmlCode.find('>', tagPosition);
    //<a href="url">Text</a>
    //                  ↑
    size_t secondOpeningBracketPosition = htmlCode.find('<', closingBracketPosition+1);

    //<a href="url">Text</a>
    //              ↑  ↑
    tag->properties.push_back({
        "visibleText", htmlCode.substr(closingBracketPosition+1, secondOpeningBracketPosition-closingBracketPosition-1)
    });


    //<a href="url">Text</a>
    // ↑          ↑
    std::string tagParams = htmlCode.substr(tagPosition+1, closingBracketPosition-tagPosition-1);


    //a href="url"
    // ↑
    size_t firstSpace = tagParams.find(' ');

    //a href="url"
    //↑
    tag->properties.push_back({
        "tagName", tagParams.substr(0, firstSpace)
    });
    tagParams.erase(0, firstSpace+1);//delete tagName and space ->    //href="url"

    size_t equalsIndex;
    while ((equalsIndex = tagParams.find('=')) != std::string::npos){
        std::string key = tagParams.substr(0, equalsIndex);
        tagParams.erase(0, equalsIndex);

        tagParams.erase(0, 2); // delete '="'

        //url"
        //   ↑
        size_t quotesPos = tagParams.find('\"');

        //"
        std::string value = tagParams.substr(0, quotesPos);
        tagParams.erase(0, quotesPos);


        tag->properties.push_back({
            key, value
        });

        tagParams.erase(0, 2); // delete "
    }

    return tag;
}



std::vector< Tag* > select(std::string &htmlCode, std::string &partOfTagCode, int amount){
    if (amount==0){ return {}; }


    size_t tagPosition = htmlCode.find(partOfTagCode); // handle first tag
    Tag* tag = getTagData(htmlCode, tagPosition);

    if (amount==1){ return {tag}; }

    int count = 1; // in order not to use result.size()
    std::vector< Tag* > result = {tag};

    while(((tagPosition = htmlCode.find(partOfTagCode, tagPosition+1)) != std::string::npos) && count<=amount){
        result.push_back(
            getTagData(htmlCode, tagPosition)
        );
    }

    return result;
}


std::string getWordData(std::string &htmlCode){

    std::string wordSelector = "span[class='headword hdb tw-bw dhw dpos-h_hw']";
    auto result = select(htmlCode, wordSelector, 0);

    return "";
}


