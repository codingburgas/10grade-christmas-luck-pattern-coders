/*
 * WordUi adapts word data for use in Qt environment by converting it from Word object.
 * It also provides functionality for checking if a specific tag is associated with the word.
 */

#include "wordUi.h"
#include "wordAlgorithms.h"


/* Constructor, which copies properties from Word object into Qt-like types.
 * This is necessary for adapting the word data to be used within a Qt environment.
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

    // Convert tags from std::string to QString and store in the tags list
    for (std::string &tag : word->tags){
        this->tags.push_back(QString::fromStdString(tag));
    }
}

/* Checks if a specified tag exists in the list of tags.
 * This function is used to determine whether the given tag is associated with the word.
 * Parameters:
 * -- tagToFind: QString, the tag to search for
 * Returns:
 * -- bool: true if the tag exists, false otherwise
 */
bool WordUi::isInTags(QString tagToFind){
    for (QString& tag : tags){
        if (tag == tagToFind){
            return true;
        }
    }
    return false;
}
