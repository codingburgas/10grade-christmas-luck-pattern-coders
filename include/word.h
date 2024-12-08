//
// Created by Oleksandr Vinichenko on 06.12.2024.
//

#ifndef WORD_H
#define WORD_H


#pragma once

#include <iostream>


struct Word{
    long id;
    std::string word;
    std::string definition;
    std::string synonym;
    std::string partOfSpeech;
    std::string difficulty;


};


std::string wordSelector();

std::string partOfSpeechSelector();

std::string difficultySelector();

std::string definitionSelector();

std::string wordLinkSelector();
/*std::string wordSelector(){
    return "<span class=\"headword hdb tw-bw dhw dpos-h_hw\"";
}*/




#endif //WORD_H
