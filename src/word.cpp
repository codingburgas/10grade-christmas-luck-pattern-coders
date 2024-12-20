//
// Created by Oleksandr Vinichenko on 06.12.2024.
//
#include <iostream>
#include <vector>

#include "../include/word.h"



std::string wordSelector(){
    return "<span class=\"hw dhw\"";
}
std::string partOfSpeechSelector(){
    return "<span class=\"pos dpos\"";
}
std::string difficultySelector(){
    return "<span class=\"epp-xref";
}
std::string definitionSelector(){
    return "<div class=\"def ddef_d db\"";
}
std::string wordLinkSelector(){
    return "<a class=\"query\"";
}


bool sameWords(Word& word1, Word& word2){

    std::vector< std::string > properties = {
        "word", "definition", "partOfSpeech", "difficulty"
    };

    for (std::string property:properties){
        if (word1.getProperty(property) != word2.getProperty(property)){
            return false;
        }
    }

    return true;
}

bool Word::operator==(Word& objectToCompare){
    return sameWords(*this, objectToCompare);
}

bool Word::operator!=(Word& objectToCompare){
    return !sameWords(*this, objectToCompare);
}
