//
// tagsui.h
// Header file defining the TagsUi object with properties related to difficulty, part of speech, and custom tags.
//

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
    TagsUi(Tags *tags);

    QList<QString> difficultyTags = {"A1", "A2", "B1", "B2", "C1", "C2"};
    QList<QString> partOfSpeechTags = {"noun", "verb", "adjective", "adverb", "suffix"};
    QList<QString> customTags;

    const QList<QString> getDifficultyTags() const { return difficultyTags; }

    Q_INVOKABLE const int getDifficultyTagsSize() const { return difficultyTags.size(); }

    void setDifficultyTags(const QList<QString>&) {}

    const QList<QString> getPartOfSpeechTags() const { return partOfSpeechTags; }

    Q_INVOKABLE const int getPartOfSpeechTagsSize() const { return partOfSpeechTags.size(); }

    void setPartOfSpeechTags(const QList<QString>&) {}

    QList<QString> getCustomTags() const { return customTags; }

    Q_INVOKABLE int getCustomTagsSize() const { return customTags.size(); }

    void setCustomTags(const QList<QString>& tags) {
        customTags = tags;
        emit customTagsChanged();
    }

    Q_INVOKABLE QString getElementOnIndex(int index);

    Q_INVOKABLE bool isInCustomTags(QString tagToFind);

signals:
    void difficultyTagsChanged();
    void partOfSpeechTagsChanged();
    void customTagsChanged();

};

#endif // TAGSUI_H
