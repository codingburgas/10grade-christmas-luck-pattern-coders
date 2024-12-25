#ifndef TAGSUI_H
#define TAGSUI_H


#include <QObject>
#include <QList>
#include <QString>

#include <iostream>
#include <vector>



#include <QObject>
#include <QList>
#include <QString>

#include "tags.h"

struct TagsUi : public QObject {
    Q_OBJECT
    Q_PROPERTY(const QList<QString> difficultyTags READ getDifficultyTags WRITE setDifficultyTags NOTIFY difficultyTagsChanged)
    Q_PROPERTY(const QList<QString> partOfSpeechTags READ getPartOfSpeechTags WRITE setPartOfSpeechTags NOTIFY partOfSpeechTagsChanged)
    Q_PROPERTY(QList<QString> customTags READ getCustomTags WRITE setCustomTags NOTIFY customTagsChanged)

public:

    /* Constructor, which copies properies from Tags object into Qt-like types
     * Parameters:
     * -- tags: Tags object
     * Returns:
     * -- Creates Tags
     */
    TagsUi(Tags *tags);

    QList<QString> difficultyTags = {"A1", "A2", "B1", "B2", "C1", "C2"};
    QList<QString> partOfSpeechTags = {"noun", "verb", "adjective", "adverb"};
    QList<QString> customTags;


    // Difficulty Tags
    const QList<QString> getDifficultyTags() const { return difficultyTags; }
    Q_INVOKABLE const int getDifficultyTagsSize() const { return difficultyTags.size(); }
    void setDifficultyTags(const QList<QString>&) {}


    // Part of Speech Tags
    const QList<QString> getPartOfSpeechTags() const { return partOfSpeechTags; }
    Q_INVOKABLE const int getPartOfSpeechTagsSize() const { return partOfSpeechTags.size(); }
    void setPartOfSpeechTags(const QList<QString>&) {}


    // Custom Tags
    QList<QString> getCustomTags() const { return customTags; }
    Q_INVOKABLE int getCustomTagsSize() const { return customTags.size(); }
    void setCustomTags(const QList<QString>& tags) {
        customTags = tags;
        emit customTagsChanged();
    }

    /* Goes through every array and returns tag on index, if all them were 1 array
     * Parameters:
     * -- index: index of tag if all arrays were 1
     * Returns:
     * -- QString: name of the tag
     */
    Q_INVOKABLE QString getElementOnIndex(int index);


    /* Checks if tag is custom
     * Parameters:
     * -- QString: name of the tag
     * Returns:
     * -- bool: whether tag is custom
     */
    Q_INVOKABLE bool isInCustomTags(QString tagToFind);

signals:
    void difficultyTagsChanged();
    void partOfSpeechTagsChanged();
    void customTagsChanged();

};



#endif // TAGSUI_H
