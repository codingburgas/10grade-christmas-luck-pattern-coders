#include "tagsUi.h"
#include "message.h"



TagsUi::TagsUi(Tags *tags){
    difficultyTags = {};
    partOfSpeechTags = {};
    customTags = {};

    for (const std::string& difficultyTag : tags->difficultyTags){
        difficultyTags.append(QString::fromStdString(difficultyTag));
    }

    for (const std::string& partOfSpeechTag : tags->partOfSpeechTags){
        partOfSpeechTags.append(QString::fromStdString(partOfSpeechTag));
    }

    for (std::string& customTag : tags->customTags){
        customTags.append(QString::fromStdString(customTag));
    }
}


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



bool TagsUi::inCustomTags(QString tagToFind){
    for (QString &tag : customTags){
        if (tag == tagToFind){
            return true;
        }
    }

    return false;
}
