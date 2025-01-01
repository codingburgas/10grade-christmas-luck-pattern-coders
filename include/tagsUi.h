#ifndef TAGSUI_H
#define TAGSUI_H

#include <QObject>
#include <QList>
#include <QString>
#include <iostream>
#include <vector>
#include "tags.h"

struct TagsUi : public QObject {
    Q_OBJECT
    Q_PROPERTY(const QList<QString> difficultyTags READ getDifficultyTags WRITE setDifficultyTags NOTIFY difficultyTagsChanged)
    Q_PROPERTY(const QList<QString> partOfSpeechTags READ getPartOfSpeechTags WRITE setPartOfSpeechTags NOTIFY partOfSpeechTagsChanged)
    Q_PROPERTY(QList<QString> customTags READ getCustomTags WRITE setCustomTags NOTIFY customTagsChanged)

public:

    /* Constructor, which copies properties from Tags object into Qt-like types
     * Parameters:
     * -- tags: Tags object
     * Returns:
     * -- Creates Tags
     */
    TagsUi(Tags *tags);

    QList<QString> difficultyTags = {"A1", "A2", "B1", "B2", "C1", "C2"};
    QList<QString> partOfSpeechTags = {"noun", "verb", "adjective", "adverb", "suffix"};
    QList<QString> customTags;

    // Difficulty Tags
    /*
     * Get the list of difficulty tags
     * Parameters:
     * -- None
     * Returns:
     * -- QList<QString>: a list of difficulty tags
     */
    const QList<QString> getDifficultyTags() const { return difficultyTags; }

    /*
     * Get the number of difficulty tags
     * Parameters:
     * -- None
     * Returns:
     * -- int: the size of the difficulty tags list
     */
    Q_INVOKABLE const int getDifficultyTagsSize() const { return difficultyTags.size(); }

    /*
     * Set the difficulty tags list (doesn't change anything here as it's a placeholder)
     * Parameters:
     * -- const QList<QString>&: list of difficulty tags
     * Returns:
     * -- None
     */
    void setDifficultyTags(const QList<QString>&) {}

    // Part of Speech Tags
    /*
     * Get the list of part of speech tags
     * Parameters:
     * -- None
     * Returns:
     * -- QList<QString>: a list of part of speech tags
     */
    const QList<QString> getPartOfSpeechTags() const { return partOfSpeechTags; }

    /*
     * Get the number of part of speech tags
     * Parameters:
     * -- None
     * Returns:
     * -- int: the size of the part of speech tags list
     */
    Q_INVOKABLE const int getPartOfSpeechTagsSize() const { return partOfSpeechTags.size(); }

    /*
     * Set the part of speech tags list (doesn't change anything here as it's a placeholder)
     * Parameters:
     * -- const QList<QString>&: list of part of speech tags
     * Returns:
     * -- None
     */
    void setPartOfSpeechTags(const QList<QString>&) {}

    // Custom Tags
    /*
     * Get the list of custom tags
     * Parameters:
     * -- None
     * Returns:
     * -- QList<QString>: a list of custom tags
     */
    QList<QString> getCustomTags() const { return customTags; }

    /*
     * Get the number of custom tags
     * Parameters:
     * -- None
     * Returns:
     * -- int: the size of the custom tags list
     */
    Q_INVOKABLE int getCustomTagsSize() const { return customTags.size(); }

    /*
     * Set the custom tags list and emit the customTagsChanged signal
     * Parameters:
     * -- const QList<QString>& tags: a list of custom tags to be set
     * Returns:
     * -- None
     */
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
