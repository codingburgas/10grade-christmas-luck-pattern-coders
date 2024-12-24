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


    std::string fileName = "words.json";

    for (json &wordData : getJsonDataFromFile(fileName)) {
        arr.push_back(new Word(wordData));
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

    tags = new Tags();
    updateTagsUi();

    qmlRegisterType<WordUi>("WordUi", 1, 0, "WordUi");
    qmlRegisterType<TagsUi>("TagsUi", 1, 0, "TagsUi");



    // Connect the 'aboutToQuit' signal to a lambda function
    QObject::connect(&app, &QCoreApplication::aboutToQuit, [&]() {
        //save tags into json file
        json tagsJson = tags->toJson();

        std::string fileName = "tags.json";
        writeJsonToFile(tagsJson, fileName);


        for (Word* word : words){ delete word; }
        for (WordUi* wordUi : wordsUi){ delete wordUi; }
        delete tagsUi;
    });


    try{
        getAllWords(words);
    }catch(Message& m){
        emit message(QString::fromStdString(m.title), QString::fromStdString(m.description), QString::fromStdString(m.type));
    } catch(...){
        emit message();
    }

    updateWordsUi();

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
void Application::updateWordsUi() {
    try {
        QList<WordUi*> result = {};
        for (Word *word : words) {
            auto wordUi = new WordUi(word);
            result.append(wordUi);
        }

        setWordsUi(result);
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
void Application::updateTagsUi(){
    try {
        TagsUi* result = new TagsUi(tags);

        setTagsUi(result);
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

        updateWordsUi();
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

        updateWordsUi();
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



void Application::deleteWordTag(int wordIndex, int tagIndex){
    try{
        // check if tagIndex is valid, because QList doesn't throw 'out of range' exception, but crashes application
        if (tagIndex < 0 || tagIndex >= wordsUi[wordIndex]->tags.size()){
            emit message("Couldn't find the tag", "Couldn't find the tag", "error");
            return;
        }


        std::string &tag = words[wordIndex]->tags[tagIndex];

        if (!contains(tags->customTags, tag)){
            emit message("This tag can not be deleted", "Tags, containing difficulty and part of speech are impossible to delete", "warning");
            return;
        }


        words[wordIndex]->tags.erase(words[wordIndex]->tags.begin() + tagIndex);
        wordsUi[wordIndex]->tags.erase(wordsUi[wordIndex]->tags.begin() + tagIndex);

        words[wordIndex]->save();

        emit wordsUi[wordIndex]->tagsChanged();


    } catch(std::out_of_range&){
        emit message("Couldn't find the word", "Couldn't find the word", "error");
    } catch(...){
        emit message();
    }
}




void Application::addWordTag(int wordIndex, int tagIndex){
    try{

        if (tagIndex < 0 || tagIndex >= tags->customTags.size()){
            emit message("Couldn't find the tag", "Couldn't find the tag", "error");
            return;
        }


        std::string &tag = tags->customTags[tagIndex];

        if (contains(words[wordIndex]->tags, tag)){
            emit message("This tag is already added", "Word already has this tag", "warning");
            return;
        }


        words[wordIndex]->tags.push_back(tag);
        wordsUi[wordIndex]->tags.append(QString::fromStdString(tag));

        words[wordIndex]->save();

        emit wordsUi[wordIndex]->tagsChanged();


    } catch(std::out_of_range&){
        emit message("Couldn't find the word", "Couldn't find the word", "error");
    } catch(...){
        emit message();
    }
}
