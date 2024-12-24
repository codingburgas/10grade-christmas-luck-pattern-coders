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


    Tags();

    json toJson();


};


#endif // TAGS_H
