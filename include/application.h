#ifndef APPLICATION_H
#define APPLICATION_H


#include <iostream>
#include <vector>
#include <QObject>
#include <QString>
#include <QList>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlListProperty>

#include "json.hpp"
using json = nlohmann::json;

#include "word.h"
#include "fileManager.h"
#include "wordAlgorithms.h"
#include "wordUi.h"
#include "tags.h"
#include "tagsUi.h"
#include "cache.h"
#include "message.h"


/*
 * Retrieves all words from a JSON file and stores them in the provided vector.
 * Parameters:
 * -- arr: vector to store the words.
 * Returns:
 * -- No return value. The words are directly stored in the vector passed by reference.
 */
void getAllWords(std::vector<Word*> &arr);

/*
 * Retrieves all tags from a JSON file and stores them in the provided vector.
 * Parameters:
 * -- arr: vector to store the tags.
 * Returns:
 * -- No return value. The words are directly stored in the vector passed by reference.
 */
void getAllTags(std::vector<std::string> &arr);








/*
 * Application structure, managing the word list, search, sorting, and updates.
 * Inherits from QObject to provide Qt-specific functionality.
 */
struct Application : public QObject {
    Q_OBJECT
    Q_PROPERTY(QList<WordUi*> wordsUi READ getWordsUi WRITE setWordsUi NOTIFY wordsUiChanged FINAL)
    Q_PROPERTY(size_t indexOfClickedWord READ getIndexOfClickedWord WRITE setIndexOfClickedWord NOTIFY indexOfClickedWordChanged FINAL)
    Q_PROPERTY(TagsUi* tagsUi READ getTagsUi WRITE setTagsUi NOTIFY tagsUiChanged FINAL)
    Q_PROPERTY(QList<QString> tagsChosenUi READ getTagsChosenUi WRITE setTagsChosenUi NOTIFY tagsChosenUiChanged)
    Q_PROPERTY(Cache* cache READ getCache WRITE setCache NOTIFY cacheChanged FINAL)
    Q_PROPERTY(QList<Message*> messagesBeforeStart READ getMessagesBeforeStart WRITE setMessagesBeforeStart NOTIFY messagesBeforeStartChanged FINAL)

public:
    //properties
    std::vector<Word*> words = {};   // List of words in the application.
    Tags* tags = {}; // Object, containing all tags used in application
    std::vector<std::string> tagsChosen = {};
    QList<QString> tagsChosenUi = {};
    size_t indexOfClickedWord;        // Index of the currently clicked word.
    QList<WordUi*> wordsUi = {};   // List of words to display.
    TagsUi* tagsUi = {}; // List of all tags
    Cache* cache = new Cache{};
    QList<Message*> messagesBeforeStart = {};

    // Qt methods ----------


    /* Returns messagesBeforeStart property
     * Parameters:
     * -- None
     * Returns:
     * -- QList<Message*>: messagesBeforeStart
     */
    QList<Message*> getMessagesBeforeStart(){
        return messagesBeforeStart;
    }


    /*
     * Gets the list of displayed words.
     * Parameters:
     * -- None
     * Returns:
     * -- wordsUi: List of words currently displayed.
     */
    QList<WordUi*> getWordsUi() {
        return wordsUi;
    }

    /*
     * Gets the list of all tags.
     * Parameters:
     * -- None
     * Returns:
     * -- tagsUi: List of tags currently displayed.
     */
    TagsUi* getTagsUi() { return tagsUi; }


    /*
     * Set messagesBeforeStart property and emits correspondent signal
     * Parameters:
     * -- QList<Message*>: new value of messagesBeforeStart
     * Returns:
     * -- None
     */
    void setMessagesBeforeStart(QList<Message*> &value){
        messagesBeforeStart = value;
        messagesBeforeStartChanged();
    }


    /*
     * Sets the list of displayed words.
     * Parameters:
     * -- val: New list of displayed words.
     * Returns:
     * -- No return value. Sets the wordsUi property.
     */
    void setWordsUi(QList<WordUi*> &val) { wordsUi = val; emit wordsUiChanged(); }

    /*
     * Sets the list of displayed Tags.
     * Parameters:
     * -- val: New list of displayed Tags.
     * Returns:
     * -- No return value. Sets the tagsUi property.
     */
    void setTagsUi(TagsUi *val) { delete tagsUi; tagsUi = val; emit tagsUiChanged(); }

    /*
     * Gets the index of the currently clicked word.
     * Parameters:
     * -- None
     * Returns:
     * -- indexOfClickedWord: Index of the clicked word.
     */
    size_t getIndexOfClickedWord() { return indexOfClickedWord; }


    /*
     * Sets the index of the currently clicked word.
     * Parameters:
     * -- val: New index of the clicked word.
     * Returns:
     * -- No return value. Sets the indexOfClickedWord property.
     */
    void setIndexOfClickedWord(size_t &val) { indexOfClickedWord = val; emit indexOfClickedWordChanged(); }


    /*
     * Returns tagsChosenUi property
     * Parameters:
     * -- None
     * Returns:
     * -- QList<QString>: tagsChosenUi
     */
    QList<QString> getTagsChosenUi() const {
        return tagsChosenUi;
    }

    /*
     * Returns cache property
     * Parameters:
     * -- None
     * Returns:
     * -- Cache*: cache object
     */
    Cache *getCache(){ return cache; }


    /*
     * Set cache property and emits correspondent signal
     * Parameters:
     * -- Cache*: new value of cache
     * Returns:
     * -- None
     */
    void setCache(Cache *val){ cache = val; emit cacheChanged(); }

    /*
     * Set tagsChosenUi property and emits correspondent signal
     * Parameters:
     * -- QList<QString>: new value of tagsChosenUi
     * Returns:
     * -- None
     */
    void setTagsChosenUi(const QList<QString> &val) { tagsChosenUi = val; emit tagsChosenUiChanged(); }


    /*
     * Updates the list of displayed words.
     * Parameters:
     * -- None
     * Returns:
     * -- No return value. Updates the WordsUi property.
     */
    Q_INVOKABLE void updateWordsUi();

    /*
     * Updates the list of displayed Tags.
     * Parameters:
     * -- None
     * Returns:
     * -- No return value. Updates the tagsUi property.
     */
    Q_INVOKABLE void updateTagsUi();


    /*
     * Updates the list of tagsChosenUi by copying values from tagsChosen into Qt-like types.
     * Parameters:
     * -- None
     * Returns:
     * -- None
     */
    Q_INVOKABLE void updateTagsChosenUi();

    /*
     * Gets the size of the displayed words list.
     * Parameters:
     * -- None
     * Returns:
     * -- Integer representing the number of displayed words.
     */
    Q_INVOKABLE int getWordsUiSize() { return wordsUi.size(); }



    /*
     * Gets the size of the tagsChosenUi.
     * Parameters:
     * -- None
     * Returns:
     * -- Integer representing the size of array.
     */
    Q_INVOKABLE int getTagsChosenUiSize() { return tagsChosenUi.size(); }


    /*
     * Searches for words based on a specified part of a word and property name.
     * Filters words according to case sensitivity, and whether the part appears at the start or end.
     * Parameters:
     * -- part: the part of the word to search for.
     * -- propertyName: the property (like word, definition, etc.) to search in.
     * -- caseSensitive: flag indicating if the search is case-sensitive.
     * -- startsWith: flag indicating if the search matches words starting with the part.
     * -- endsWith: flag indicating if the search matches words ending with the part.
     * Returns:
     * -- No return value. Updates the displayed words after filtering.
     */
    Q_INVOKABLE void searchWords(QString part, QString propertyName, bool caseSensitive, bool startsWith = false, bool endsWith = false);

    /*
     * Sorts the words by a specified property in either ascending or descending order.
     * Parameters:
     * -- propertyName: the property by which to sort the words.
     * -- ascendingOrder: flag indicating if the sorting is in ascending order (true) or descending order (false).
     * Returns:
     * -- No return value. The words are sorted and displayed in the updated order.
     */
    Q_INVOKABLE void sortWords(QString propertyName, bool ascendingOrder = true);

    /*
     * Increases the frequency of use for a specific word.
     * Parameters:
     * -- wordIndex: the index of the word in the list to update.
     * Returns:
     * -- No return value. The word's frequency of use is updated.
     */
    Q_INVOKABLE void increaseWordFrequncyOfUse(int wordIndex);


    /* Removes a tag from the word and saves changes to a file
     * Parameters:
     * --wordIndex: index of the word in 'words' array
     * --tagIndex: index of the tag in 'customTags' array of tags object
     * Returns:
     * --None
     */
    Q_INVOKABLE void deleteWordTag(int wordIndex, int tagIndex);


    /* Adds a tag to word and saves changes to a file
     * Parameters:
     * --wordIndex: index of the word in 'words' array
     * --tagIndex: index of the tag in 'customTags' array of tags object
     * Returns:
     * --None
     */
    Q_INVOKABLE void addWordTag(int wordIndex, int tagIndex);


    /* Adds a tag, which can be then applied to a word or search filter
     * Parameters:
     * --tag: a name of new tag
     * Returns:
     * --None
     */
    Q_INVOKABLE void addTag(QString tag);


    /* Deletes tag by removing it from 'customTags' array and removing all occurences of specified tag in words
     * Parameters:
     * --tag: a name of tag to be deleted
     * Returns:
     * --None
     */
    Q_INVOKABLE void deleteTag(int tagIndex);


    /*
     * Adds tag to chosen(for search)
     * Parameters:
     * -- None
     * Returns:
     * -- None
     */
    Q_INVOKABLE void addTagToChosen(int tagIndex);


    /*
     * Removes tag from chosen(for search)
     * Parameters:
     * -- None
     * Returns:
     * -- None
     */
    Q_INVOKABLE void removeTagFromChosen(int tagIndex);


    /*
     * Checks if tag is in chosen
     * Parameters:
     * -- tag: name of the tag
     * Returns:
     * -- bool: whether tag is in chosen or not
     */
    Q_INVOKABLE bool isInTagsChosen(QString tag);


    /*Function that can be invoked from qml and returns amount of syllables in word
     * Parameters:
     * --wordIndex - index of the word
     * Returns:
     * --amount of its syllables as a string
    */
    Q_INVOKABLE QString countSyllablesOfWord(int wordIndex);

    /*Resets chosen tags
     * Parameters:
     * -- None
     * Returns:
     * -- None
    */
    Q_INVOKABLE void resetTagsChosen();


    /*Returns size of MessagesBeforeStart property
     * Parameters:
     * -- None
     * Returns:
     * --int: size
    */
    Q_INVOKABLE int getMessagesBeforeStartSize(){ return messagesBeforeStart.size(); }

    // -----------------------------

    /*
     * Starts and runs the Qt application.
     * Parameters:
     * -- argc: number of command-line arguments.
     * -- argv: array of command-line arguments.
     * Returns:
     * -- Integer representing the application's exit code.
     */
    int run(int argc, char *argv[]);


    /* Removes all occurences of specified tag in file with words
     * Parameters:
     * --tag: a name of tag to be deleted
     * Returns:
     * --None
     */
    void deleteTagInData(std::string& tag);

signals:
    void wordsUiChanged();
    void tagsUiChanged();
    void tagsChosenUiChanged();
    void indexOfClickedWordChanged();
    void cacheChanged();
    void messagesBeforeStartChanged();
    void message(QString title = "Something went wrong :(", QString description = "Unknown error", QString type = "error");

    void wordTagsChanged();
};

#endif // APPLICATION_H
