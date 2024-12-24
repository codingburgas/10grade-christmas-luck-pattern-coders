#include "wordUi.h"

WordUi::WordUi(Word *word){
    this->word = QString::fromStdString(word->word);
    this->definition = QString::fromStdString(word->definition);
    this->partOfSpeech = QString::fromStdString(word->partOfSpeech);
    this->difficulty = QString::fromStdString(word->difficulty);
    this->url = QString::fromStdString(word->url);
    this->frequencyOfUse = word->frequencyOfUse;
    //this->word = QString::fromStdString(word->word);

    for (std::string &tag : word->tags){
        this->tags.append(QString::fromStdString(tag));
    }
}
