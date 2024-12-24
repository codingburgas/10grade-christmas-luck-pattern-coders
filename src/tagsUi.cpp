#include "tagsUi.h"



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
