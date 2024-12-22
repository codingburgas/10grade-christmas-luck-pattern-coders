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
using json=nlohmann::json;

#include "word.h"
#include "fileManager.h"


struct Application : public QObject{
    Q_OBJECT
    Q_PROPERTY(QString test READ getTest WRITE setTest NOTIFY testChanged FINAL)
    Q_PROPERTY(QList<QList<QString>> displayedWords READ getDisplayedWords WRITE setDisplayedWords NOTIFY displayedWordsChanged FINAL)

public:
    QString test = "Oleksandr";
    /*std::vector<Word*> words = {new Word{
        "apple",
        "definition of an apple",
        "noun",
        "a1",
        "https://dictionary.cambridge.org/dictionary/english/apple",
        52
    }
    };*/
    std::vector<Word*> words = {};
    QList<QList<QString>> displayedWords = {};

    // Qt thing ----------
    QString getTest(){ return test; }
    void setTest(QString &val){ test=val; }

    QList<QList<QString>> getDisplayedWords(){ return displayedWords; }
    void setDisplayedWords(QList<QList<QString>> &val){ displayedWords=val; }



    Q_INVOKABLE void updateDisplayedWords(){
        QList<QList<QString>> result = {};
        for (Word* word : words){
            //words.append(QString::fromStdString(word->word));
            QList<QString> wordData = {
                QString::fromStdString(word->word),
                QString::fromStdString(word->definition),
                QString::fromStdString(word->partOfSpeech),
                QString::fromStdString(word->difficulty),
                QString::fromStdString(word->url),
                QString::number(word->frequencyOfUse)
            };

            result.append(wordData);
        }

        setDisplayedWords(result);
    }
    // -----------------------------




    int run(int argc, char *argv[]);


signals:
    void testChanged();
    void displayedWordsChanged();

};



void getAllWords(std::vector<Word*> &arr);





#endif // APPLICATION_H
