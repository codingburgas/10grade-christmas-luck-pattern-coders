#ifndef TAGS_H
#define TAGS_H

#include <iostream>
#include <vector>


#include "json.hpp"
using json=nlohmann::json;




struct Tags{
    const std::vector<std::string> difficultyTags = {"A1", "A2", "B1", "B2", "C1", "C2"};
    const std::vector<std::string> partOfSpeechTags = {"noun", "verb", "adjective", "adverb"};
    std::vector<std::string> customTags = {};


    /* Constructor, which reads custom tags from file and adds them to customTags property
     * Parameters:
     * -- None
     * Returns:
     * -- Creates Tags
     */
    Tags();



    /* Converts necessary data into json object
     * Parameters:
     * -- None
     * Returns:
     * -- json: json representation of the Tags object
     */
    json toJson();


    /* Goes through every array and returns tag on index, if all them were 1 array
     * Parameters:
     * -- index: index of tag if all arrays were 1
     * Returns:
     * -- std::string: name of the tag
     */
    std::string getElementOnIndex(size_t index);


};


#endif // TAGS_H
