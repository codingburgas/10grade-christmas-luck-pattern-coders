//
// Created by Oleksandr Vinichenko on 06.12.2024.
//

#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <vector>

#include "json.hpp"
using json=nlohmann::json;   //type alias

struct Tag{
    //name, value
    std::vector<std::vector< std::string >> properties = {};

    std::string getProperty(std::string key){
        for (auto keyValue : properties){
            if (keyValue[0] == key){
                return (keyValue[1].empty()) ? "Undefined value.": keyValue[1];
            }
        }

        return "Undefined value.";
    }

};




Tag getTagData(std::string &htmlCode, size_t &tagPosition);




//                                                                              max value
std::vector<Tag> select(std::string &htmlCode, const std::string &partOfTagCode, int amount=100);


json getWordData(std::string &htmlCode);



#endif //PARSER_H
