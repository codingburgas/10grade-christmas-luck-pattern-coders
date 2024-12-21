//
// word.h
// Header file, which makes it easy to interact with data related to words
//


#ifndef WORD_H
#define WORD_H


#pragma once

#include <iostream>
#include <vector>

#include "json.hpp"
using json=nlohmann::json;


struct Word {
    //long id;
    std::string word;
    std::string definition;
    std::string partOfSpeech;
    std::string difficulty;
    std::string url;


    /*
     * Retrieves the value of a specified property from the Word structure.
     * Parameters:
     * --property: The name of the property to retrieve. It should be one of the following:
     *   - "word": Retrieves the word itself.
     *   - "definition": Retrieves the definition of the word.
     *   - "url": Retrieves the URL associated with the word.
     *   - "partOfSpeech": Retrieves the part of speech of the word.
     *   - "difficulty": Retrieves the difficulty level of the word.
     * Returns:
     * --std::string: The value of the specified property.
     */
    std::string getProperty(const std::string &property);



    /*
     * Compares two Word objects for inequality.
     * Parameters:
     * --objectToCompare: The Word object to compare with the current object.
     * Returns:
     * --bool: Returns true if the two Word objects are considered unequal, otherwise false.
     */
    bool operator!=(Word& objectToCompare);

    /*
     * Compares two Word objects for equality.
     * Parameters:
     * --objectToCompare: The Word object to compare with the current object.
     * Returns:
     * --bool: Returns true if the two Word objects are considered equal, otherwise false.
     */
    bool operator==(Word& objectToCompare);
};


/*
  * Returns the HTML selector for the word.
  * Returns:
  * --std::string: The HTML span element selector for the word.
  */
std::string wordSelector();

/*
  * Returns the HTML selector for the part of speech.
  * Returns:
  * --std::string: The HTML span element selector for the part of speech.
  */
std::string partOfSpeechSelector();

/*
  * Returns the HTML selector for the difficulty level.
  * Returns:
  * --std::string: The HTML span element selector for difficulty.
  */
std::string difficultySelector();

/*
  * Returns the HTML selector for the definition.
  * Returns:
  * --std::string: The HTML div element selector for the definition.
  */
std::string definitionSelector();

/*
  * Returns the HTML selector for the word link.
  * Returns:
  * --std::string: The HTML anchor element selector for the word link.
  */
std::string wordLinkSelector();


/*
 * Retrieves all URLs from the provided JSON data.
 * Parameters:
 * --jsonData: The JSON data to extract URLs from.
 * Returns:
 * --std::vector<std::string>: A vector containing all the URLs found in the JSON data.
 */
std::vector<std::string> getWordsLinks(json jsonData);




#endif //WORD_H
