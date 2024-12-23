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
#include "wordAlgorithms.h"


void getAllWords(std::vector<Word*> &arr);



struct Application : public QObject{
    Q_OBJECT
    Q_PROPERTY(QList<QList<QString>> displayedWords READ getDisplayedWords WRITE setDisplayedWords NOTIFY displayedWordsChanged FINAL)
    Q_PROPERTY(size_t indexOfClickedWord READ getIndexOfClickedWord WRITE setIndexOfClickedWord NOTIFY indexOfClickedWordChanged FINAL)


public:
    //properties
    std::vector<Word*> words = {};
    size_t indexOfClickedWord;
    QList<QList<QString>> displayedWords = {};

    // Qt methods ----------
    QList<QList<QString>> getDisplayedWords(){ return displayedWords; }
    void setDisplayedWords(QList<QList<QString>> &val){ displayedWords=val; emit displayedWordsChanged(); }

    size_t getIndexOfClickedWord(){ return indexOfClickedWord; }
    void setIndexOfClickedWord(size_t &val){ indexOfClickedWord=val; emit indexOfClickedWordChanged(); }



    Q_INVOKABLE void updateDisplayedWords();

    Q_INVOKABLE int getDisplayedWordsSize(){ return displayedWords.size(); }

    Q_INVOKABLE void searchWords(QString part, QString propertyName);

    Q_INVOKABLE void sortWords(QString propertyName, bool ascendingOrder=true);

    Q_INVOKABLE void increaseWordFrequncyOfUse(int wordIndex);
    // -----------------------------




    int run(int argc, char *argv[]);


signals:
    void displayedWordsChanged();
    void indexOfClickedWordChanged();
    void message(QString title = QString::fromStdString("Something went wrong :("), QString description = QString::fromStdString("Unknown error"), QString type = QString::fromStdString("error"));

};









#endif // APPLICATION_H
