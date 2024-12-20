//
// Created by Oleksandr Vinichenko on 06.12.2024.
//

#ifndef WORD_H
#define WORD_H


#pragma once

#include <iostream>


struct Word {
    //long id;
    std::string word;
    std::string definition;
    std::string synonym;
    std::string partOfSpeech;
    std::string difficulty;

    std::string getProperty(const std::string &property) {
        if (property == "word") {
            return word;
        } else if (property == "definition") {
            return definition;
        } else if (property == "synonym") {
            return synonym;
        } else if (property == "partOfSpeech") {
            return partOfSpeech;
        } else if (property == "difficulty") {
            return difficulty;
        } else {
            throw std::invalid_argument("Invalid property name: " + property);
        }
    }
};


std::string wordSelector();

std::string partOfSpeechSelector();

std::string difficultySelector();

std::string definitionSelector();

std::string wordLinkSelector();





#endif //WORD_H
