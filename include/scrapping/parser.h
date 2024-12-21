//
// parser.h
// Header file, which parses html
//

#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <vector>

#include "json.hpp"
using json=nlohmann::json;   //type alias

struct Tag{
    //key, value
    std::vector<std::vector< std::string >> properties = {};


    /*
     * Retrieves the value of a specified property from the Tag structure.
     * Parameters:
     * --property: The name of the property to retrieve.
     * Returns:
     * --std::string: The value of the specified property.
     */
    std::string getProperty(std::string key){
        for (auto keyValue : properties){
            if (keyValue[0] == key){
                return (keyValue[1].empty()) ? "Undefined value.": keyValue[1];
            }
        }

        return "Undefined value.";
    }


    /*
     * Compares two Tag objects for equality.
     * Parameters:
     * --tagToCompare: The Tag object to compare with the current object.
     * Returns:
     * --bool: Returns true if the two Tag objects are considered equal, otherwise false.
     */
    bool operator ==(Tag &tagToCompare){
        for (std::vector<std::string> property : properties){
            if (property[1] != tagToCompare.getProperty(property[0])) return false;
        }

        return true;
    }

    /*
     * Compares two Tag objects for inequality.
     * Parameters:
     * --tagToCompare: The Tag object to compare with the current object.
     * Returns:
     * --bool: Returns true if the two Tag objects are considered inequal, otherwise false.
     */
    bool operator !=(Tag &tagToCompare){
        return !(*this==tagToCompare);
    }

};



/*
 * Parses tag data from an HTML string
 * Parameters:
 * -- htmlCode: reference to the HTML code string
 * -- tagPosition: reference to the position of the tag in the HTML string
 * Returns:
 * -- Tag: an object containing tag properties and visible text
 */
Tag getTagData(std::string &htmlCode, size_t &tagPosition);




/*
 * Selects and returns a list of tags from an HTML string that match a specific pattern
 * Parameters:
 * -- htmlCode: reference to the HTML code string
 * -- partOfTagCode: part of the tag code to search for
 * -- amount: maximum number of tags to retrieve
 * Returns:
 * -- std::vector<Tag>: a vector of parsed tags
 */
std::vector<Tag> select(std::string &htmlCode, const std::string &partOfTagCode, int amount=100);


/*
 * Extracts word data from an HTML string
 * Parameters:
 * -- htmlCode: reference to the HTML code string
 * Returns:
 * -- json: a JSON object containing word details (e.g., word, definition, part of speech, difficulty)
 */
json getWordData(std::string &htmlCode);



#endif //PARSER_H
