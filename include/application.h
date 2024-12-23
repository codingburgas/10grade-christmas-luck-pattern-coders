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


public:
    //properties
    std::vector<Word*> words = {};
    QList<QList<QString>> displayedWords = {};

    // Qt methods ----------
    QList<QList<QString>> getDisplayedWords(){ return displayedWords; }
    void setDisplayedWords(QList<QList<QString>> &val){ displayedWords=val; emit displayedWordsChanged(); }



    Q_INVOKABLE void updateDisplayedWords();

    Q_INVOKABLE int getDisplayedWordsSize(){ return displayedWords.size(); }

    Q_INVOKABLE void searchWords(QString part, QString propertyName);

    Q_INVOKABLE void sortWords(QString propertyName, bool ascendingOrder=true);

    Q_INVOKABLE void increaseWordFrequncyOfUse(int wordIndex);
    // -----------------------------




    int run(int argc, char *argv[]);


signals:
    void displayedWordsChanged();

};









#endif // APPLICATION_H
