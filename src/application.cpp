#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCoreApplication>
#include <QQmlContext>

#include "application.h"
#include "message.h"

template<typename T>
bool contains(std::vector<T> &v, T &val){
    for (T& el : v){
        if (el == val){
            return true;
        }
    }

    return false;
}

/*
 * Retrieves all words from a JSON file and stores them in the provided vector.
 * Parameters:
 * -- arr: vector to store the words.
 * Returns:
 * -- No return value. The words are directly stored in the vector passed by reference.
 */
void getAllWords(std::vector<Word*> &arr) {
    arr = {};
    //tags = {};

    std::string fileName = "words.json";
    for (json &wordData : getJsonDataFromFile(fileName)) {
        arr.push_back(convertJsonToWord(wordData));
        /*for (json& tag : wordData["tags"]){
            std::string strTag = tag.get<std::string>();
            if (!contains(tags, strTag)){
                tags.push_back(strTag);
            }
        }*/
    }
}



/*
 * Retrieves all tags from a JSON file and stores them in the provided vector.
 * Parameters:
 * -- arr: vector to store the tags.
 * Returns:
 * -- No return value. The words are directly stored in the vector passed by reference.
 */
void getAllTags(std::vector<std::string> &arr){
    arr = {};

    std::string fileName = "tags.json";
    for (json& tag : getJsonDataFromFile(fileName)){
        arr.push_back(tag.get<std::string>());
    }
}


/*
 * Initializes and runs the application.
 * Parameters:
 * -- argc: number of command-line arguments.
 * -- argv: array of command-line arguments.
 * Returns:
 * -- The application's execution result (exit code).
 */
int Application::run(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterType<WordUi>("WordUi", 1, 0, "WordUi");


    // Connect the 'aboutToQuit' signal to a lambda function
    QObject::connect(&app, &QCoreApplication::aboutToQuit, [&]() {
        //save tags into json file
        json tagsJson = json::parse("[]");
        for (std::string &tag : tags){
            tagsJson.push_back(tag);
        }

        std::string fileName = "tags.json";
        writeJsonToFile(tagsJson, fileName);


        for (Word* word : words){ delete word; }
        for (WordUi* wordUi : displayedWords){ delete wordUi; }
    });


    getAllWords(words);
    updateDisplayedWords();

    engine.rootContext()->setContextProperty("application", this);

    engine.load(QUrl(QStringLiteral("qrc:/ui/Application.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}

/*
 * Updates the displayed list of words by converting each word into a list of strings.
 * The data is then assigned to the displayedWords property.
 * Parameters:
 * -- None
 * Returns:
 * -- No return value. Updates the displayedWords property.
 */
void Application::updateDisplayedWords() {
    try {
        QList<WordUi*> result = {};
        for (Word *word : words) {
            auto wordUi = new WordUi(word);
            result.append(wordUi);
        }

        setDisplayedWords(result);
    } catch (Message& m) {
        emit message(QString::fromStdString(m.title), QString::fromStdString(m.description), QString::fromStdString(m.type));
    } catch (...) {
        emit message();
    }
}


/*
 * Updates the list of displayed Tags.
 * Parameters:
 * -- None
 * Returns:
 * -- No return value. Updates the displayedTags property.
 */
void Application::updateDisplayedTags(){
    try {
        QList<QString> result = {};
        for (std::string strTag : tags) {
            QString tag = QString::fromStdString(strTag);

            result.append(tag);
        }

        setDisplayedTags(result);
    } catch (Message& m) {
        emit message(QString::fromStdString(m.title), QString::fromStdString(m.description), QString::fromStdString(m.type));
    } catch (...) {
        emit message();
    }
}

/*
 * Searches for words based on a specified part of a word and property name.
 * Filters words according to case sensitivity, and whether the part appears at the start or end.
 * Parameters:
 * -- part: the part of the word to search for.
 * -- propertyName: the property (like word, definition, etc.) to search in.
 * -- caseSensitive: flag indicating if the search is case-sensitive.
 * -- startsWith: flag indicating if the search matches words starting with the part.
 * -- endsWith: flag indicating if the search matches words ending with the part.
 * Returns:
 * -- No return value. Updates the displayed words after filtering.
 */
void Application::searchWords(QString part, QString propertyName, bool caseSensitive, bool startsWith, bool endsWith) {
    try {
        getAllWords(words);
        std::string strPart = part.toStdString();
        std::string strPropertyName = propertyName.toStdString();
        leaveWordsWithSpecificPart(words, strPart, strPropertyName, caseSensitive, startsWith, endsWith);

        updateDisplayedWords();
    } catch (Message& m) {
        emit message(QString::fromStdString(m.title), QString::fromStdString(m.description), QString::fromStdString(m.type));
    } catch (...) {
        emit message();
    }
}

/*
 * Sorts the words by a specified property in either ascending or descending order.
 * Parameters:
 * -- propertyName: the property by which to sort the words.
 * -- ascendingOrder: flag indicating if the sorting is in ascending order (true) or descending order (false).
 * Returns:
 * -- No return value. The words are sorted and displayed in the updated order.
 */
void Application::sortWords(QString propertyName, bool ascendingOrder) {
    try {
        std::string strPropertyName = propertyName.toStdString();

        sortByProperty(words, strPropertyName, ascendingOrder);

        updateDisplayedWords();
    } catch (Message& m) {
        emit message(QString::fromStdString(m.title), QString::fromStdString(m.description), QString::fromStdString(m.type));
    } catch (...) {
        emit message();
    }
}

/*
 * Increases the frequency of use for a specific word.
 * Parameters:
 * -- wordIndex: the index of the word in the list to update.
 * Returns:
 * -- No return value. The word's frequency of use is updated.
 */
void Application::increaseWordFrequncyOfUse(int wordIndex) {
    try {
        Word* word = words[wordIndex];

        word->frequencyOfUse++;

        word->save();
    } catch (Message& m) {
        emit message(QString::fromStdString(m.title), QString::fromStdString(m.description), QString::fromStdString(m.type));
    } catch (...) {
        emit message();
    }
}
