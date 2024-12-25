#include "tags.h"
#include "fileManager.h"
#include "message.h"


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



std::string Tags::getElementOnIndex(size_t index){
    if (index < 0){
        throw Message("Unexpected error", "Tag index is invalid.", "error");
    }

    if (index < difficultyTags.size()){
        return difficultyTags[index];
    }

    index -= difficultyTags.size();

    if (index < partOfSpeechTags.size()){
        return partOfSpeechTags[index];
    }

    index -= partOfSpeechTags.size();

    if(index < customTags.size()){
        return customTags[index];
    }

    throw Message("Couldn't find tag", "Tag index is invalid.", "error");
}
