
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



    engine.load(QUrl(QStringLiteral("qrc:/ui/main.qml")));
    if (engine.rootObjects().isEmpty()){
        return -1;
    }

    return app.exec();

}
