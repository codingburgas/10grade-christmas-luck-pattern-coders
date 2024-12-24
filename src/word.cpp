//
// word.cpp
// C++ file, which makes it easy to interact with data related to words
//

#include <iostream>
#include <vector>
#include <cctype>    // For std::tolower

#include "word.h"
#include "message.h"
#include "fileManager.h"



/*
 * Returns the HTML selector for the word.
 * Returns:
 * --std::string: The HTML span element selector for the word.
 */
std::string wordSelector(){
    return "<span class=\"hw dhw\"";
}

/*
 * Returns the HTML selector for the part of speech.
 * Returns:
 * --std::string: The HTML span element selector for the part of speech.
 */
std::string partOfSpeechSelector(){
    return "<span class=\"pos dpos\"";
}

/*
 * Returns the HTML selector for the difficulty level.
 * Returns:
 * --std::string: The HTML span element selector for difficulty.
 */
std::string difficultySelector(){
    return "<span class=\"epp-xref";
}

/*
 * Returns the HTML selector for the definition.
 * Returns:
 * --std::string: The HTML div element selector for the definition.
 */
std::string definitionSelector(){
    return "<div class=\"def ddef_d db\"";
}

/*
 * Returns the HTML selector for the word link.
 * Returns:
 * --std::string: The HTML anchor element selector for the word link.
 */
std::string wordLinkSelector(){
    return "<a class=\"query\"";
}

/*
 * Compares two Word objects for equality based on specific properties.
 * Parameters:
 * --word1: The first Word object to compare.
 * --word2: The second Word object to compare.
 * Returns:
 * --bool: Returns true if all the properties of the two Word objects are equal, otherwise false.
 */
bool sameWords(Word& word1, Word& word2){

    std::vector< std::string > properties = {
        "word", "definition", "partOfSpeech", "difficulty"
    };

    for (std::string &property:properties){
        if (word1.getProperty(property) != word2.getProperty(property)){
            return false;
        }
    }

    return true;
}


/*
 * Retrieves the value of a specified property from the Word structure.
 * Parameters:
 * --property: The name of the property to retrieve. It should be one of the following:
 *   - "word": Retrieves the word itself.
 *   - "definition": Retrieves the definition of the word.
 *   - "url": Retrieves the URL associated with the word.
 *   - "partOfSpeech": Retrieves the part of speech of the word.
 *   - "difficulty": Retrieves the difficulty level of the word.
 * Returns:
 * --std::string: The value of the specified property.
 */
std::string Word::getProperty(const std::string &property){

    if (property == "word") {
        return word;
    } else if (property == "definition") {
        return definition;
    } else if (property == "url") {
        return url;
    } else if (property == "partOfSpeech") {
        return partOfSpeech;
    } else if (property == "difficulty") {
        return difficulty;
    } else if (property == "frequncyOfUse"){
        return std::to_string(frequencyOfUse);
    }else {
        //throw std::invalid_argument("Invalid property name: " + property);
        throw Message("Something went wrong :( ", "Invalid property name", "error");
    }

}


/*
 * Converts the Word object to a JSON representation.
 * Parameters:
 * -- None
 * Returns:
 * -- A JSON object representing the word with properties: word, definition, partOfSpeech, difficulty, url, frequencyOfUse and tags.
 */
json Word::toJson() {
    json wordData;
    wordData["word"] = word;
    wordData["definition"] = definition;
    wordData["partOfSpeech"] = partOfSpeech;
    wordData["difficulty"] = difficulty;
    wordData["url"] = url;
    wordData["frequencyOfUse"] = frequencyOfUse;
    wordData["tags"] = tags;

    return wordData;
}


/*Saves changes in Word object to a file
 *Parameters:
 *--None
 *Returns:
 *--None
 */
void Word::save(){
    std::string fileName = "words.json";
    json data = getJsonDataFromFile(fileName);

    json wordData = toJson();
    size_t wordIndex = std::string::npos;

    // Search for the word in the JSON data
    for (size_t i = 0; i < data.size(); i++) {
        if (data[i] == wordData) {
            wordIndex = i;
            break;
        }
    }

    if (wordIndex != std::string::npos) {
        data[wordIndex] = wordData;
    } else {
        // Throw an error if the word is not found
        throw Message("Couldn't find the word", "Couldn't find the word", "error");
    }

    // Write the updated JSON data back to the file
    writeJsonToFile(data, fileName);
}



/*
 * Compares two Word objects for equality.
 * Parameters:
 * --objectToCompare: The Word object to compare with the current object.
 * Returns:
 * --bool: Returns true if the two Word objects are considered equal, otherwise false.
 */
bool Word::operator==(Word& objectToCompare){
    return sameWords(*this, objectToCompare);
}

/*
 * Compares two Word objects for inequality.
 * Parameters:
 * --objectToCompare: The Word object to compare with the current object.
 * Returns:
 * --bool: Returns true if the two Word objects are considered unequal, otherwise false.
 */
bool Word::operator!=(Word& objectToCompare){
    return !sameWords(*this, objectToCompare);
}

/*
 * Converts JSON data to a Word object.
 * Parameters:
 * --jsonData: The JSON data to convert into a Word object.
 * Returns:
 * --Word*: A pointer to a newly created Word object.
 */
Word* convertJsonToWord(json &jsonData){
    Word *word = new Word{};

    try{
        word->word = jsonData["word"];
    }catch(...){}

    try{
        word->definition = jsonData["definition"];
    }catch(...){}

    try{
        word->url = jsonData["url"];
    }catch(...){}

    try{
        word->partOfSpeech = jsonData["partOfSpeech"];
    }catch(...){}

    try{
        word->difficulty = jsonData["difficulty"];
    }catch(...){}

    try{
        word->frequencyOfUse = jsonData["frequencyOfUse"];
    } catch(...){}

    try{
        //word->tags = jsonData["tags"];
        for (json& tag : jsonData["tags"]){
            std::string strTag = tag.get<std::string>();
            word->tags.push_back(strTag);
        }
    } catch(...){}

    return word;
}

/*
 * Retrieves all URLs from the provided JSON data.
 * Parameters:
 * --jsonData: The JSON data to extract URLs from.
 * Returns:
 * --std::vector<std::string>: A vector containing all the URLs found in the JSON data.
 */
std::vector<std::string> getWordsLinks(json jsonData){
    if (jsonData.is_array()){
        std::vector<std::string> result={};
        for (json wordInJson : jsonData){
            result.push_back(wordInJson["url"]);
        }
        return result;
    } else{
        return {jsonData["url"]};
    }
}



/*
 * Counts the number of syllables in a given word recursively.
 * Parameters:
 * --word: The input string representing the word to analyze.
 * --index: The current character index being processed in the word.
 * --syllableCount: The running count of syllables found so far.
 * --prevWasVowel: A boolean indicating whether the previous character was a vowel.
 * Returns:
 * --int: The total number of syllables in the word after processing all characters.
 */
int countSyllables(const std::string& word, int index, int syllableCount, bool prevWasVowel) {
    if (word.empty()) return 0;

    const std::string vowels = "aeiouy";

    if (index == word.size()) {
        // Handle the ending adjustments
        if (word.size() > 2 && word.substr(word.size() - 2) == "le" && vowels.find(tolower(word[word.size() - 3])) == std::string::npos) {
            syllableCount++;
        }

        if (word.size() > 2 && word.substr(word.size() - 2) == "ia"){
            syllableCount++;
        }
        if (word.size() > 1 && word[word.size() - 1] == 'e') {
            syllableCount--;
        }
        return syllableCount > 0 ? syllableCount : 1;
    }

    bool isVowel = vowels.find(tolower(word[index])) != std::string::npos;
    if (isVowel && !prevWasVowel) {
        syllableCount++;
    }

    return countSyllables(word, index + 1, syllableCount, isVowel);
}
