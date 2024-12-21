//
// Created by Oleksandr Vinichenko on 06.12.2024.
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

    std::string getProperty(const std::string &property) {
        if (property == "word") {
            return word;
        } else if (property == "definition") {
            return definition;
        } else if (property == "url") {
            return url;
        } else if (property == "partOfSpeech") {
            return partOfSpeech;
        } else if (property == "difficulty") {
            return difficulty;
        } else {
            throw std::invalid_argument("Invalid property name: " + property);
        }
    }



    bool operator!=(Word& objectToCompare);
    bool operator==(Word& objectToCompare);
};


std::string wordSelector();

std::string partOfSpeechSelector();

std::string difficultySelector();

std::string definitionSelector();

std::string wordLinkSelector();


std::vector<std::string> getWordsLinks(json jsonData);




#endif //WORD_H
