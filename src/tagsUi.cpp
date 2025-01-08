/* Constructor, which copies properies from Tags object into Qt-like types
 * Parameters:
 * -- tags: Tags object
 * Returns:
 * -- Creates Tags
 */

#include "tagsUi.h"
#include "message.h"

TagsUi::TagsUi(Tags *tags){
    difficultyTags = {};
    partOfSpeechTags = {};
    customTags = {};

    for (const std::string& difficultyTag : tags->difficultyTags){
        difficultyTags.push_back(QString::fromStdString(difficultyTag));
    }

    for (const std::string& partOfSpeechTag : tags->partOfSpeechTags){
        partOfSpeechTags.push_back(QString::fromStdString(partOfSpeechTag));
    }

    for (std::string& customTag : tags->customTags){
        customTags.push_back(QString::fromStdString(customTag));
    }
}



/* Goes through every array and returns tag on index, if all them were 1 array
 * Parameters:
 * -- index: index of tag if all arrays were 1
 * Returns:
 * -- QString: name of the tag
 */
QString TagsUi::getElementOnIndex(int index){
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


/* Checks if tag is custom
 * Parameters:
 * -- QString: name of the tag
 * Returns:
 * -- bool: whether tag is custom
 */
bool TagsUi::isInCustomTags(QString tagToFind){
    for (QString &tag : customTags){
        if (tag == tagToFind){
            return true;
        }
    }

    return false;
}
