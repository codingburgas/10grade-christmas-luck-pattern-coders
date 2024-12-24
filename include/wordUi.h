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
    /*WordUi() {}
    WordUi(const WordUi &other);

    WordUi &operator=(const WordUi &other);*/

    WordUi(const WordUi& other){
        word = other.word;
        definition = other.definition;
        partOfSpeech = other.partOfSpeech;
        difficulty = other.difficulty;
        url = other.url;
        frequencyOfUse = other.frequencyOfUse;
        tags = other.tags;
    }


    WordUi& operator=(const WordUi& other){
        if (this != &other) { // Protect against self-assignment
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
    QString getWord() const { return word; }
    QString getDefinition() const { return definition; }
    QString getPartOfSpeech() const { return partOfSpeech; }
    QString getDifficulty() const { return difficulty; }
    QString getUrl() const { return url; }
    unsigned long getFrequencyOfUse() const { return frequencyOfUse; }
    QList<QString> getTags() const { return tags; }

    // Setters
    void setWord(const QString& value) {
        if (word != value) {
            word = value;
            emit wordChanged();
        }
    }

    void setDefinition(const QString& value) {
        if (definition != value) {
            definition = value;
            emit definitionChanged();
        }
    }

    void setPartOfSpeech(const QString& value) {
        if (partOfSpeech != value) {
            partOfSpeech = value;
            emit partOfSpeechChanged();
        }
    }

    void setDifficulty(const QString& value) {
        if (difficulty != value) {
            difficulty = value;
            emit difficultyChanged();
        }
    }

    void setUrl(const QString& value) {
        if (url != value) {
            url = value;
            emit urlChanged();
        }
    }

    void setFrequencyOfUse(unsigned long value) {
        if (frequencyOfUse != value) {
            frequencyOfUse = value;
            emit frequencyOfUseChanged();
        }
    }

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
