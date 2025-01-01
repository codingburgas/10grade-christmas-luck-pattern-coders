#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCoreApplication>
#include <QQmlContext>

#include "application.h"
#include "wordAlgorithms.h"
#include "message.h"
#include "cache.h"
#include <QDebug>


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


    qmlRegisterType<WordUi>("WordUi", 1, 0, "WordUi");
    qmlRegisterType<TagsUi>("TagsUi", 1, 0, "TagsUi");
    qmlRegisterType<Cache>("Cache", 1, 0, "Cache");
    qmlRegisterType<Message>("Message", 1, 0, "Message");

    qRegisterMetaType<QList<Message>>("QList<Message>");





    // Connect the 'aboutToQuit' signal to a lambda function
    QObject::connect(&app, &QCoreApplication::aboutToQuit, [&]() {
        //save tags into json file
        json tagsJson = tags->toJson();

        std::string fileName = "tags.json";
        writeJsonToFile(tagsJson, fileName);


        for (Word* word : words){ delete word; }
        for (WordUi* wordUi : wordsUi){ delete wordUi; }
        for (Message* message : messagesBeforeStart){ delete message; }
        delete tagsUi;
        delete cache;
    });

    QObject::connect(this->cache, &Cache::pageChanged, [&](){
        qDebug() << "Page in cache changed to " << cache->page << "\n";
    });



    try{
        getAllWords(words);
        updateWordsUi();
    }catch(Message& m){
        //emit message(QString::fromStdString(m.title), QString::fromStdString(m.description), QString::fromStdString(m.type));
        messagesBeforeStart.push_back(new Message(m));
    } catch(...){
        //emit message("Failed to load words", "Application may work incorrectly. Try reloading it", "error");
        messagesBeforeStart.push_back(new Message("Failed to load words", "Application may work incorrectly. Try reloading it", "error"));
    }


    try{
        tags = new Tags();
        updateTagsUi();
    } catch(Message& m){
        //emit message(QString::fromStdString(m.title), QString::fromStdString(m.description), QString::fromStdString(m.type));
        messagesBeforeStart.push_back(new Message(m));

    } catch(...){
        messagesBeforeStart.push_back(new Message("Failed to load words", "Application may work incorrectly. Try reloading it", "error"));
        //emit message("Failed to load tags", "Application may work incorrectly. Try reloading it", "error");
    }



    engine.rootContext()->setContextProperty("application", this);

    engine.load(QUrl(QStringLiteral("qrc:/ui/Application.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}

/*
 * Updates the wordsUi list by copying values from words into Qt-like types
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
            result.push_back(wordUi);
        }

        setWordsUi(result);
    } catch (Message& m) {
        emit message(QString::fromStdString(m.title), QString::fromStdString(m.description), QString::fromStdString(m.type));
    } catch (...) {
        emit message();
    }
}


/*
 * Updates the list of tagsUi by copying values from tags into Qt-like types.
 * Parameters:
 * -- None
 * Returns:
 * -- None.
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
        if (strPart.size() != 0){
            leaveWordsWithSpecificPart(words, strPart, strPropertyName, caseSensitive, startsWith, endsWith);
        }
        leaveWordsWithSpecificTags(words, tagsChosen);

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

        wordsUi[wordIndex]->frequencyOfUse++;
    } catch (Message& m) {
        emit message(QString::fromStdString(m.title), QString::fromStdString(m.description), QString::fromStdString(m.type));
    } catch (...) {
        emit message();
    }
}



/* Removes a tag from the word and saves changes to a file
 * Parameters:
 * --wordIndex: index of the word in 'words' array
 * --tagIndex: index of the tag in 'customTags' array of tags object
 * Returns:
 * --None
 */
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

        //emit wordsUi[wordIndex]->tagsChanged();
        emit wordTagsChanged();


    } catch(std::out_of_range&){
        emit message("Couldn't find the word", "Couldn't find the word", "error");
    } catch(...){
        emit message();
    }
}



/* Adds a tag to word and saves changes to a file
 * Parameters:
 * --wordIndex: index of the word in 'words' array
 * --tagIndex: index of the tag in 'customTags' array of tags object
 * Returns:
 * --None
 */
void Application::addWordTag(int wordIndex, int tagIndex){
    try{

        if (tagIndex < 0 || tagIndex >= (tags->partOfSpeechTags.size() + tags->difficultyTags.size() + tags->customTags.size())){
            emit message("Couldn't find the tag", "Couldn't find the tag", "error");
            return;
        }


        //std::string &tag = tags->customTags[tagIndex];
        std::string tag = tags->getElementOnIndex(tagIndex);

        if (contains(words[wordIndex]->tags, tag)){
            emit message("This tag is already added", "Word already has this tag", "warning");
            return;
        }


        words[wordIndex]->tags.push_back(tag);
        wordsUi[wordIndex]->tags.push_back(QString::fromStdString(tag));

        words[wordIndex]->save();

        //emit wordsUi[indexOfClickedWord]->tagsChanged();
        emit wordTagsChanged();


    } catch(std::out_of_range&){
        emit message("Couldn't find the word", "Couldn't find the word", "error");
    } catch(...){
        emit message();
    }
}


/* Adds a tag, which can be then applied to a word or search filter
 * Parameters:
 * --tag: a name of new tag
 * Returns:
 * --None
 */
void Application::addTag(QString tag){
    std::string strTag = tag.toStdString();
    if (contains(tags->customTags, strTag)){
        emit message("This tag is already added", "Word already has this tag", "warning");
        return;
    }

    try{
        tags->customTags.push_back(strTag);
        tagsUi->customTags.push_back(tag);

        //emit tagsUiChanged();
        tagsUi->customTagsChanged();
    } catch(...){
        emit message();
    }

}


/* Removes all occurences of specified tag in file with words
 * Parameters:
 * --tag: a name of tag to be deleted
 * Returns:
 * --None
 */
void Application::deleteTagInData(std::string& tag){

    std::string fileName = "words.json";


    json data = getJsonDataFromFile(fileName);
    for (json &wordData : data){
        //wordData["tags"].erase(std::remove(wordData["tags"].begin(), wordData["tags"].end(), tag), wordData["tags"].end());
        for (size_t i=wordData["tags"].size()-1; i > 1; i--){
            if (wordData["tags"][i] == tag){
                wordData["tags"].erase(i);
            }
        }
        //wordData["tags"].erase(tag);
    }

    writeJsonToFile(data, fileName);

    for (Word* word: words){
        for (size_t i=word->tags.size()-1; i>1; i--){
            if (word->tags[i] == tag){
                word->tags.erase(word->tags.begin() + i);
            }
        }
    }


    try {
        QList<WordUi*> result = {};
        for (Word *word : words) {
            auto wordUi = new WordUi(word);
            result.push_back(wordUi);
        }

        wordsUi = result;
    } catch (Message& m) {
        emit message(QString::fromStdString(m.title), QString::fromStdString(m.description), QString::fromStdString(m.type));
    } catch (...) {
        emit message();
    }

}


/* Deletes tag by removing it from 'customTags' array and removing all occurences of specified tag in words
 * Parameters:
 * --tag: a name of tag to be deleted
 * Returns:
 * --None
 */
void Application::deleteTag(int tagIndex){
    int notCustomTagsSize = tags->partOfSpeechTags.size() + tags->difficultyTags.size();

    if (tagIndex >= (tags->customTags.size() + notCustomTagsSize)){
        emit message("Couldn't find the tag", "Couldn't find the tag", "error");
        return;
    }
    if (tagIndex < notCustomTagsSize){
        emit message("Cannot delete part of speech and difficulty tags", "Cannot delete part of speech and difficulty tags", "error");
        return;
    }

    try{
        std::string tag = tags->getElementOnIndex(tagIndex);


        tags->customTags.erase(tags->customTags.begin() + tagIndex - notCustomTagsSize);
        tagsUi->customTags.erase(tagsUi->customTags.begin() + tagIndex - notCustomTagsSize);

        //emit tagsUiChanged();


        deleteTagInData(tag);

        emit tagsUi->customTagsChanged();
    } catch (Message& m) {
        emit message(QString::fromStdString(m.title), QString::fromStdString(m.description), QString::fromStdString(m.type));
    } catch (...) {
        emit message();
    }

}


/*
 * Updates the list of tagsChosenUi by copying values from tagsChosen into Qt-like types.
 * Parameters:
 * -- None
 * Returns:
 * -- None
 */
void Application::updateTagsChosenUi(){
    tagsChosenUi = {};

    for (std::string& tagChosen : tagsChosen){
        tagsChosenUi.push_back(QString::fromStdString(tagChosen));
    }

    emit tagsChosenUiChanged();
}


/*
 * Adds tag to chosen(for search)
 * Parameters:
 * -- None
 * Returns:
 * -- None
 */
void Application::addTagToChosen(int tagIndex){
    try{
        std::string tag = tags->getElementOnIndex(tagIndex);

        if (contains(tagsChosen, tag)){
            emit message("Tag is already added", "Tag is already added", "error");
            return;
        }

        tagsChosen.push_back(tag);
        tagsChosenUi.push_back(QString::fromStdString(tag));

        emit tagsChosenUiChanged();

    } catch (Message& m) {
        emit message(QString::fromStdString(m.title), QString::fromStdString(m.description), QString::fromStdString(m.type));
    } catch (...) {
        emit message();
    }

}


/*
 * Removes tag from chosen(for search)
 * Parameters:
 * -- None
 * Returns:
 * -- None
 */
void Application::removeTagFromChosen(int tagIndex){
    try{
        if (tagIndex >= tagsChosen.size()) {
            emit message("Couldn't find the tag", "Couldn't find the tag", "error");
            return;
        }

        tagsChosen.erase(tagsChosen.begin() + tagIndex);
        tagsChosenUi.erase(tagsChosenUi.begin() + tagIndex);

        emit tagsChosenUiChanged();

    } catch(std::out_of_range&){
        emit message("Couldn't find the tag", "Couldn't find the tag", "error");
    } catch (...) {
        emit message();
    }
}


/*
 * Checks if tag is in chosen
 * Parameters:
 * -- tag: name of the tag
 * Returns:
 * -- bool: whether tag is in chosen or not
 */
bool Application::isInTagsChosen(QString tag){
    std::string strTag = tag.toStdString();

    return contains(tagsChosen, strTag);
}



QString Application::countSyllablesOfWord(int wordIndex){
    return QString::number(countSyllables(words[wordIndex]->word));
}



void Application::resetTagsChosen(){
    try{
        tagsChosen.clear();
        tagsChosenUi.clear();

        emit tagsChosenUiChanged();
    }catch(...){
        emit message();
    }
}
