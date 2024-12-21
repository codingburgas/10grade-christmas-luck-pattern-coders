//
// Created by Oleksandr Vinichenko on 06.12.2024.
//
#include <iostream>
#include <vector>

#include "word.h"



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

Word* convertJsonToWord(json &jsonData){
    Word *word = new Word{};

    try{
        word->word = jsonData["word"];
    }catch(...){}

    try{
        word->definition = jsonData["definition"];
    }catch(...){}

    try{
        word->partOfSpeech = jsonData["partOfSpeech"];
    }catch(...){}

    try{
        word->difficulty = jsonData["difficulty"];
    }catch(...){}

    return word;

}

std::vector<std::string> getWordsLinks(json jsonData){

    if (jsonData.is_array()){
        std::vector<std::string> result={};
        for (json wordInJson : jsonData){
            result.push_back(wordInJson["url"]);
        }
        return result;
    } else{
        return {jsonData["url"]};
    }
}
