#include "tags.h"
#include "fileManager.h"
#include "message.h"


/* Constructor, which reads custom tags from file and adds them to customTags property
 * Parameters:
 * -- None
 * Returns:
 * -- Creates Tags
 */
Tags::Tags(){
    std::string fileName = "tags.json";

    json tags = getJsonDataFromFile(fileName);

    for (std::string tag : tags){
        customTags.push_back(tag);
    }
}


/* Converts necessary data into json object
 * Parameters:
 * -- None
 * Returns:
 * -- json: json representation of the Tags object
 */
json Tags::toJson(){
    json result = json::parse("[]");

    for (std::string &tag : customTags){
        result.push_back(tag);
    }

    return result;
}


/* Goes through every array and returns tag on index, if all them were 1 array
 * Parameters:
 * -- index: index of tag if all arrays were 1
 * Returns:
 * -- std::string: name of the tag
 */
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
