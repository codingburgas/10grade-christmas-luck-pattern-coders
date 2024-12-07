//
// Created by Oleksandr Vinichenko on 06.12.2024.
//

#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <vector>

struct Tag{
    //name, value
    std::vector<std::vector< std::string >> properties;
};


Tag *getTagData(std::string &htmlCode, size_t &tagPosition);




//                                                                              max value
std::vector<Tag*> select(std::string &htmlCode, std::string &partOfTagCode, int amount=100);


std::string getWordData(std::string &htmlCode);



#endif //PARSER_H
