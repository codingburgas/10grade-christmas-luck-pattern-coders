#ifndef WORDUI_H
#define WORDUI_H

#include <QObject>
#include <QString>
#include <QList>

#include "word.h"


struct WordUi : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString word READ getWord WRITE setWord NOTIFY wordChanged)
    Q_PROPERTY(QString definition READ getDefinition WRITE setDefinition NOTIFY definitionChanged)
    Q_PROPERTY(QString partOfSpeech READ getPartOfSpeech WRITE setPartOfSpeech NOTIFY partOfSpeechChanged)
    Q_PROPERTY(QString difficulty READ getDifficulty WRITE setDifficulty NOTIFY difficultyChanged)
    Q_PROPERTY(QString url READ getUrl WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(unsigned long frequencyOfUse READ getFrequencyOfUse WRITE setFrequencyOfUse NOTIFY frequencyOfUseChanged)
    Q_PROPERTY(QList<QString> tags READ getTags WRITE setTags NOTIFY tagsChanged)

public:
    QString word;
    QString definition;
    QString partOfSpeech;
    QString difficulty;
    QString url;
    unsigned long frequencyOfUse = 0;
    QList<QString> tags = {};

    WordUi(Word *word);


    // constructor of copying(for being able to use this type in QList)
    WordUi(const WordUi& other){
        word = other.word;
        definition = other.definition;
        partOfSpeech = other.partOfSpeech;
        difficulty = other.difficulty;
        url = other.url;
        frequencyOfUse = other.frequencyOfUse;
        tags = other.tags;
    }

    // asignment operator(for being able to use this type in QList)
    WordUi& operator=(const WordUi& other){
        if (this != &other) {
            word = other.word;
            definition = other.definition;
            partOfSpeech = other.partOfSpeech;
            difficulty = other.difficulty;
            url = other.url;
            frequencyOfUse = other.frequencyOfUse;
            tags = other.tags;
        }
        return *this;
    }

    // Getters
    /*
     * Retrieves the word.
     * Parameters:
     * -- None
     * Returns:
     * -- QString: the word
     */
    QString getWord() const { return word; }

    /*
     * Retrieves the definition of the word.
     * Parameters:
     * -- None
     * Returns:
     * -- QString: the definition
     */
    QString getDefinition() const { return definition; }

    /*
     * Retrieves the part of speech of the word.
     * Parameters:
     * -- None
     * Returns:
     * -- QString: the part of speech
     */
    QString getPartOfSpeech() const { return partOfSpeech; }

    /*
     * Retrieves the difficulty level of the word.
     * Parameters:
     * -- None
     * Returns:
     * -- QString: the difficulty level
     */
    QString getDifficulty() const { return difficulty; }

    /*
     * Retrieves the URL associated with the word.
     * Parameters:
     * -- None
     * Returns:
     * -- QString: the URL
     */
    QString getUrl() const { return url; }

    /*
     * Retrieves the frequency of use of the word.
     * Parameters:
     * -- None
     * Returns:
     * -- unsigned long: the frequency of use
     */
    unsigned long getFrequencyOfUse() const { return frequencyOfUse; }

    /*
     * Retrieves the tags associated with the word.
     * Parameters:
     * -- None
     * Returns:
     * -- QList<QString>: the list of tags
     */
    QList<QString> getTags() const { return tags; }

    /*
     * Sets the word.
     * Parameters:
     * -- value: QString, the new word to set
     * Returns:
     * -- None
     */
    void setWord(const QString& value) {
        if (word != value) {
            word = value;
            emit wordChanged();
        }
    }

    /*
     * Sets the definition of the word.
     * Parameters:
     * -- value: QString, the new definition to set
     * Returns:
     * -- None
     */
    void setDefinition(const QString& value) {
        if (definition != value) {
            definition = value;
            emit definitionChanged();
        }
    }

    /*
     * Sets the part of speech of the word.
     * Parameters:
     * -- value: QString, the new part of speech to set
     * Returns:
     * -- None
     */
    void setPartOfSpeech(const QString& value) {
        if (partOfSpeech != value) {
            partOfSpeech = value;
            emit partOfSpeechChanged();
        }
    }

    /*
     * Sets the difficulty level of the word.
     * Parameters:
     * -- value: QString, the new difficulty level to set
     * Returns:
     * -- None
     */
    void setDifficulty(const QString& value) {
        if (difficulty != value) {
            difficulty = value;
            emit difficultyChanged();
        }
    }

    /*
     * Sets the URL associated with the word.
     * Parameters:
     * -- value: QString, the new URL to set
     * Returns:
     * -- None
     */
    void setUrl(const QString& value) {
        if (url != value) {
            url = value;
            emit urlChanged();
        }
    }

    /*
     * Sets the frequency of use of the word.
     * Parameters:
     * -- value: unsigned long, the new frequency of use to set
     * Returns:
     * -- None
     */
    void setFrequencyOfUse(unsigned long value) {
        if (frequencyOfUse != value) {
            frequencyOfUse = value;
            emit frequencyOfUseChanged();
        }
    }

    /*
     * Sets the tags associated with the word.
     * Parameters:
     * -- value: QList<QString>, the new tags to set
     * Returns:
     * -- None
     */
    void setTags(const QList<QString>& value) {
        if (tags != value) {
            tags = value;
            emit tagsChanged();
        }
    }



    Q_INVOKABLE int getTagsSize(){ return tags.size(); }

signals:
    void wordChanged();
    void definitionChanged();
    void partOfSpeechChanged();
    void difficultyChanged();
    void urlChanged();
    void frequencyOfUseChanged();
    void tagsChanged();

};

#endif // WORDUI_H
