#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>

struct Message{
public:
    std::string title;
    std::string description;
    std::string type;

    /*Message(const std::string& title, const std::string& description, const std::string& type){
        this->title = title;
        this->description = description;
        this->type = type;
    }*/


    Message(const std::string title, const std::string description, const std::string type){
        this->title = title;
        this->description = description;
        this->type = type;
    }

};


#endif // MESSAGE_H
