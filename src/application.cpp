
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>


#include "application.h"

void getAllWords(std::vector<Word *> &arr){
    arr = {};

    std::string fileName = "words.json";
    for (json &wordData : getJsonDataFromFile(fileName)){
        arr.push_back( convertJsonToWord(wordData) );
    }

}



int Application::run(int argc, char *argv[]){

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;


    getAllWords(words);
    updateDisplayedWords();


    engine.rootContext()->setContextProperty("application", this);



    engine.load(QUrl(QStringLiteral("qrc:/ui/Application.qml")));
    if (engine.rootObjects().isEmpty()){
        return -1;
    }

    return app.exec();

}


void Application::updateDisplayedWords(){
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



void Application::searchWords(QString part, QString propertyName){
    getAllWords(words);
    std::string strPart = part.toStdString();
    std::string strPropertyName = propertyName.toStdString();
    leaveWordsWithSpecificPart(words, strPart, strPropertyName, true);

    updateDisplayedWords();
}



void Application::sortWords(QString propertyName, bool ascendingOrder){
    std::string strPropertyName = propertyName.toStdString();

    sortByProperty(words, strPropertyName, ascendingOrder);

    updateDisplayedWords();
}



void Application::increaseWordFrequncyOfUse(int wordIndex){
    Word* word = words[wordIndex];

    word->increaseFrequencyOfUse();

    //updateDisplayedWords();
}
