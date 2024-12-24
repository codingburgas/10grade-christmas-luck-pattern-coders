#include "tags.h"
#include "fileManager.h"


Tags::Tags(){
    std::string fileName = "tags.json";

    json tags = getJsonDataFromFile(fileName);

    for (std::string tag : tags){
        customTags.push_back(tag);
    }
}


json Tags::toJson(){
    json result = json::parse("[]");

    for (std::string &tag : customTags){
        result.push_back(tag);
    }

    return result;
}
