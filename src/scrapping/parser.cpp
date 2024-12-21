//
// parser.cpp
// C++ file, which parses html
//


#include <iostream>
#include <string>
#include <vector>

#include "json.hpp"
using json=nlohmann::json;

#include "scrapping/parser.h"
#include "word.h"

/*
 * Extracts text enclosed in double quotes from a given string
 * Parameters:
 * -- text: reference to the string to search
 * -- firstQuotePosition: reference to the position of the first quote in the string
 * Returns:
 * -- std::string: the extracted text between quotes
 */
std::string getTextInQuotes(std::string &text, size_t &firstQuotePosition){
    size_t secondQuotePosition = text.find('"', firstQuotePosition+1);
    return text.substr(firstQuotePosition+1, secondQuotePosition-firstQuotePosition-1);
}

/*
 * Parses tag data from an HTML string
 * Parameters:
 * -- htmlCode: reference to the HTML code string
 * -- tagPosition: reference to the position of the tag in the HTML string
 * Returns:
 * -- Tag: an object containing tag properties and visible text
 */
Tag getTagData(std::string &htmlCode, size_t &tagPosition){
    //<div class="content">Text <a href="url_to_and">and</a> another text</div>
    Tag tag = {};

    //<div class="content">Text <a href="url_to_and">and</a> another text</div>
    //                    ↑
    size_t closingBracketPosition = htmlCode.find('>', tagPosition);

    //<div class="content">Text <a href="url_to_and">and</a> another text</div>
    // ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑
    std::string tagParams = htmlCode.substr(tagPosition+1, closingBracketPosition-tagPosition-1);

    //<div class="content">Text <a href="url_to_and">and</a> another text</div>
    // ↑↑↑
    size_t firstSpace = tagParams.find(' ');
    std::string tagName = tagParams.substr(0, firstSpace);

    //class="content"
    tagParams.erase(0, firstSpace+1); // Remove tag name and space

    //<div class="content">Text <a href="url_to_and">and</a> another text</div>
    //                                                              ↑
    std::string closingTag = "</"+tagName+">";
    size_t closingTagPosition = htmlCode.find(closingTag, tagPosition);

    //<div class="content">Text <a href="url_to_and">and</a> another text</div>
    //↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑
    std::string tagHtmlCode = htmlCode.substr(tagPosition, closingTagPosition+closingTag.size()-tagPosition);
    tag.properties.push_back({"outerHTML", tagHtmlCode});

    //<div class="content">Text <a href="url_to_and">and</a> another text</div>
    //                     ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑
    std::string textInsideTag = htmlCode.substr(closingBracketPosition+1, closingTagPosition-closingBracketPosition-1);
    std::string tagVisibleText = "";

    //<div class="content">Text <a href="url_to_and">and</a> another text</div>
    //                          ↑
    size_t nextTagIndex;
    while((nextTagIndex = textInsideTag.find("<")) != std::string::npos) {
        //Text <a href="url_to_and">and</a> another text
        //↑↑↑↑↑
        std::string justTextWithoutTag = textInsideTag.substr(0, nextTagIndex);
        tagVisibleText += justTextWithoutTag;

        //Text <a href="url_to_and">and</a> another text
        //     ↑
        Tag childTag = getTagData(textInsideTag, nextTagIndex);
        tagVisibleText += childTag.getProperty("visibleText");

        // another text
        textInsideTag.erase(0, justTextWithoutTag.size() + childTag.getProperty("outerHTML").size());
    }
    // another text
    tagVisibleText += textInsideTag; // Add remaining text

    tag.properties.push_back({"visibleText", tagVisibleText});


    // class="content"
    //      ↑
    size_t equalsIndex;
    while ((equalsIndex = tagParams.find('=')) != std::string::npos) {
        //class="content"
        //↑↑↑↑↑
        std::string key = tagParams.substr(0, equalsIndex);

        //content"
        tagParams.erase(0, equalsIndex + 2); // delete key and the '="'

        //content"
        //       ↑
        size_t quotesPos = tagParams.find('"');
        //content"
        //↑↑↑↑↑↑↑
        std::string value = tagParams.substr(0, quotesPos);
        // (nothing left in this exmple)
        tagParams.erase(0, quotesPos + 2); // Skip value and the closing quote

        tag.properties.push_back({key, value});

    }

    return tag;
}

/*
 * Selects and returns a list of tags from an HTML string that match a specific pattern
 * Parameters:
 * -- htmlCode: reference to the HTML code string
 * -- partOfTagCode: part of the tag code to search for
 * -- amount: maximum number of tags to retrieve
 * Returns:
 * -- std::vector<Tag>: a vector of parsed tags
 */
std::vector<Tag> select(std::string &htmlCode, const std::string &partOfTagCode, int amount){
    if (amount == 0) return {};

    size_t tagPosition = htmlCode.find(partOfTagCode); // Handle the first tag

    if (tagPosition == std::string::npos){
        Tag blankTag = {};

        // add essential properties
        blankTag.properties.push_back({
            "outerHTML", ""
        });
        blankTag.properties.push_back({
            "visibleText", ""
        });
        return { blankTag };
    }

    Tag tag = getTagData(htmlCode, tagPosition);

    if (amount == 1) {
        return {tag};
    }

    int count = 1; // In order not to use result.size()
    std::vector<Tag> result = {tag};

    // Retrieve subsequent matching tags
    while (( (tagPosition = htmlCode.find(partOfTagCode, tagPosition+1)) != std::string::npos ) && ( count < amount) ) {
        result.push_back( getTagData(htmlCode, tagPosition) );
        count++;
    }

    return result;
}

/*
 * Extracts word data from an HTML string
 * Parameters:
 * -- htmlCode: reference to the HTML code string
 * Returns:
 * -- json: a JSON object containing word details (e.g., word, definition, part of speech, difficulty)
 */
json getWordData(std::string &htmlCode){
    json result;

    result["word"] = select(htmlCode, wordSelector(), 1)[0].getProperty("visibleText");


    std::vector<Tag> definitions = select(htmlCode, definitionSelector());
    std::string definitionToAdd = "";


    for (Tag definition : definitions){
        std::string visibleText = definition.getProperty("visibleText");

        // don't add the plural form of the word
        if (visibleText.find("plural of") != std::string::npos){
            return json({});
        }

        // try to find real definition(sometimes firstly comes spelling)
        if (visibleText.find("US spelling of") == std::string::npos){
            size_t colonPosition = visibleText.find(":");
            if (colonPosition != std::string::npos) visibleText.erase(colonPosition); // Remove trailing ":"
            definitionToAdd = visibleText;
            break;
        }
    }


    result["definition"] = definitionToAdd;

    result["partOfSpeech"] = select(htmlCode, partOfSpeechSelector(), 1)[0].getProperty("visibleText");
    result["difficulty"] = select(htmlCode, difficultySelector(), 1)[0].getProperty("visibleText");

    return result;
}
