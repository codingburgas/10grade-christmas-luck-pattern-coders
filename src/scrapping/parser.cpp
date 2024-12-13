#include <iostream>
#include <string>
#include <vector>

#include "json.hpp"
using json=nlohmann::json;

#include "scrapping/parser.h"
#include "word.h"




std::string getTextInQuotes(std::string &text, size_t &firstQuotePosition){
    size_t secondQuotePosition = text.find('"', firstQuotePosition+1);

    return text.substr(firstQuotePosition+1, secondQuotePosition-firstQuotePosition-1);
}


Tag getTagData(std::string &htmlCode, size_t &tagPosition){
    //<a href="url">Text</a>
    Tag tag = {};

    try{
        //<a href="url">Text</a>
        //             ↑
        size_t closingBracketPosition = htmlCode.find('>', tagPosition);


        //<a href="url">Text</a>
        // ↑          ↑
        std::string tagParams = htmlCode.substr(tagPosition+1, closingBracketPosition-tagPosition-1);


        //a href="url"
        // ↑
        size_t firstSpace = tagParams.find(' ');

        /*//a href="url"
    //↑
    tag->properties.push_back({
        "tagName", tagParams.substr(0, firstSpace)
    });*/
        std::string tagName = tagParams.substr(0, firstSpace);
        tagParams.erase(0, firstSpace+1);//delete tagName and space ->    //href="url"


        std::string closingTag = "</"+tagName+">";
        //<a href="url">Text</a>
        //                  ↑
        size_t closingTagPosition = htmlCode.find(closingTag, tagPosition);

        std::string tagHtmlCode = htmlCode.substr(tagPosition, closingTagPosition+closingTag.size()-tagPosition);
        tag.properties.push_back({
            "outerHTML", tagHtmlCode
        });

        std::string textInsideTag = htmlCode.substr(closingBracketPosition+1, closingTagPosition-closingBracketPosition-1);

        /*//<a href="url">Text</a>
    //              ↑  ↑
    tag->properties.push_back({
        "visibleText", htmlCode.substr(closingBracketPosition+1, closingTagPosition-closingBracketPosition-1)
    });*/

        std::string tagVisibleText = "";
        size_t nextTagIndex = textInsideTag.find("<");


        while((nextTagIndex = textInsideTag.find("<")) != std::string::npos){
            std::string justTextWithoutTag = textInsideTag.substr(0, nextTagIndex);
            tagVisibleText += justTextWithoutTag;


            Tag childTag = getTagData(textInsideTag, nextTagIndex);
            tagVisibleText += childTag.getProperty("visibleText");
            textInsideTag.erase(0, justTextWithoutTag.size() + childTag.getProperty("outerHTML").size());

        }
        tagVisibleText += textInsideTag; // add what's left

        tag.properties.push_back({
            "visibleText", tagVisibleText
        });



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


            tag.properties.push_back({
                key, value
            });

            tagParams.erase(0, 2); // delete "
        }

    } catch(...){
        std::cout << "Exception while handling tag parsing\n";
    }


    return tag;
}



std::vector< Tag > select(std::string &htmlCode, const std::string &partOfTagCode, int amount){
    if (amount==0){ return {}; }


    size_t tagPosition = htmlCode.find(partOfTagCode); // handle first tag


    Tag tag = getTagData(htmlCode, tagPosition);

    if (amount==1){
        std::vector< Tag > result = {};
        result.push_back(tag);
        return result;
    }

    int count = 1; // in order not to use result.size()
    std::vector<Tag> result = {tag};

    while(((tagPosition = htmlCode.find(partOfTagCode, tagPosition+1)) != std::string::npos) && count<=amount){
        result.push_back(
            getTagData(htmlCode, tagPosition)
        );
        count++;
    }

    return result;
}



json getWordData(std::string &htmlCode){

    json result;



    result["word"] = select(htmlCode, wordSelector(), 1)[0].properties[1][1];
    std::string definition = select(htmlCode, definitionSelector(), 1)[0].properties[1][1];
    result["definition"] =  definition.substr(0, definition.size()-2);
    //                              crop ": "
    result["partOfSpeech"] = select(htmlCode, partOfSpeechSelector(), 1)[0].properties[1][1];
    result["difficulty"] = select(htmlCode, difficultySelector(), 1)[0].properties[1][1];

    return result;

}



