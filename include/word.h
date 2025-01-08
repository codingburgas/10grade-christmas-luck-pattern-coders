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

    std::string word;
    std::string definition;
    std::string partOfSpeech;
    std::string difficulty;
    std::string url;
    unsigned long frequencyOfUse = 0;
    std::vector<std::string> tags = {};

    Word(std::string word = "", std::string definition = "", std::string partOfSpeech = "", std::string difficulty = "", std::string url = "", unsigned long frequencyOfUse = 0, std::vector<std::string> tags = {});

    /*
     * Converts JSON data to a Word object.
     * Parameters:
     * --jsonData: The JSON data to convert into a Word object.
     * Returns:
     * --Word*: A pointer to a newly created Word object.
     */
    Word(json &jsonData);


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


    /*
     * Converts the Word object to a JSON representation.
     * Parameters:
     * -- None
     * Returns:
     * -- A JSON object representing the word with properties: word, definition, partOfSpeech, difficulty, url, and frequencyOfUse.
     */
    json toJson();


    /*
     * Increases the frequency of use of the word and updates the word's frequency in the corresponding JSON file.
     * If the word is found in the JSON file, its frequencyOfUse is incremented by 1.
     * If the word is not found, an error message is thrown.
     * Parameters:
     * -- None
     * Returns:
     * -- No return value. The frequencyOfUse property is updated, and the JSON file is rewritten.
     */
    void increaseFrequencyOfUse();


    /*Saves changes in Word object to a file
     *Parameters:
     *--None
     *Returns:
     *--None
     */
    void save();
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



/*
 * Counts the number of syllables in a given word recursively.
 * Parameters:
 * --word: The input string representing the word to analyze.
 * --index: The current character index being processed in the word.
 * --syllableCount: The running count of syllables found so far.
 * --prevWasVowel: A boolean indicating whether the previous character was a vowel.
 * Returns:
 * --int: The total number of syllables in the word after processing all characters.
 */
int countSyllables(const std::string& word, int index=0, int syllableCount=0, bool prevWasVowel=false);











#endif //WORD_H
