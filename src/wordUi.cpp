#include "wordUi.h"


/* Constructor, which copies properies from Word object into Qt-like types
 * Parameters:
 * -- word: Word object
 * Returns:
 * -- None
 */
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
