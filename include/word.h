//
// Created by Oleksandr Vinichenko on 06.12.2024.
//

#ifndef WORD_H
#define WORD_H

#include <iostream>


struct WORD{
    long id;
    std::string word;
    std::string definition;
    std::string synonym;
    std::string partOfSpeech;
    std::string difficulty;



};


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
    return "<span class=\"def ddef_d db\"";
}
/*std::string wordSelector(){
    return "<span class=\"headword hdb tw-bw dhw dpos-h_hw\"";
}*/

#endif //WORD_H
