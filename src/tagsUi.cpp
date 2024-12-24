#include "tagsUi.h"



TagsUi::TagsUi(Tags *tags){
    for (const std::string& difficultyTag : tags->difficultyTags){
        this->difficultyTags.append(QString::fromStdString(difficultyTag));
    }

    for (const std::string& partOfSpeechTag : tags->partOfSpeechTags){
        this->partOfSpeechTags.append(QString::fromStdString(partOfSpeechTag));
    }

    for (std::string& customTag : tags->customTags){
        this->customTags.append(QString::fromStdString(customTag));
    }
}
