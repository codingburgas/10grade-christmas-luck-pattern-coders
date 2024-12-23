#ifndef APPLICATION_H
#define APPLICATION_H


#include <iostream>
#include <vector>
#include <QObject>
#include <QString>
#include <QList>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "json.hpp"
using json = nlohmann::json;

#include "word.h"
#include "fileManager.h"
#include "wordAlgorithms.h"


/*
 * Retrieves all words from a JSON file and stores them in the provided vector.
 * Parameters:
 * -- arr: vector to store the words.
 * Returns:
 * -- No return value. The words are directly stored in the vector passed by reference.
 */
void getAllWords(std::vector<Word*> &arr);


/*
 * Application structure, managing the word list, search, sorting, and updates.
 * Inherits from QObject to provide Qt-specific functionality.
 */
struct Application : public QObject {
    Q_OBJECT
    Q_PROPERTY(QList<QList<QString>> displayedWords READ getDisplayedWords WRITE setDisplayedWords NOTIFY displayedWordsChanged FINAL)
    Q_PROPERTY(size_t indexOfClickedWord READ getIndexOfClickedWord WRITE setIndexOfClickedWord NOTIFY indexOfClickedWordChanged FINAL)

public:
    //properties
    std::vector<Word*> words = {};   // List of words in the application.
    size_t indexOfClickedWord;        // Index of the currently clicked word.
    QList<QList<QString>> displayedWords = {};   // List of words to display.

    // Qt methods ----------

    /*
     * Gets the list of displayed words.
     * Parameters:
     * -- None
     * Returns:
     * -- displayedWords: List of words currently displayed.
     */
    QList<QList<QString>> getDisplayedWords() { return displayedWords; }

    /*
     * Sets the list of displayed words.
     * Parameters:
     * -- val: New list of displayed words.
     * Returns:
     * -- No return value. Sets the displayedWords property.
     */
    void setDisplayedWords(QList<QList<QString>> &val) { displayedWords = val; emit displayedWordsChanged(); }

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
     * Updates the list of displayed words.
     * Parameters:
     * -- None
     * Returns:
     * -- No return value. Updates the displayedWords property.
     */
    Q_INVOKABLE void updateDisplayedWords();

    /*
     * Gets the size of the displayed words list.
     * Parameters:
     * -- None
     * Returns:
     * -- Integer representing the number of displayed words.
     */
    Q_INVOKABLE int getDisplayedWordsSize() { return displayedWords.size(); }

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

signals:
    void displayedWordsChanged();
    void indexOfClickedWordChanged();
    void message(QString title = QString::fromStdString("Something went wrong :("), QString description = QString::fromStdString("Unknown error"), QString type = QString::fromStdString("error"));
};

#endif // APPLICATION_H
