#include <iostream>
#include <vector>
#include <fstream>
#include <curl/curl.h>

#include "json.hpp"
using json=nlohmann::json;

#include "scrapping/scrapper.h"
#include "word.h"
#include "scrapping/parser.h"
#include "fileManager.h"

/*
 * Checks if a vector contains a specific value
 * Parameters:
 * -- vector: pointer to the vector to search
 * -- value: value to check for in the vector
 * Returns:
 * -- bool: true if the value is found, false otherwise
 */
template <typename T>
bool contains(std::vector<T> *vector, T value){
    for (T element : *vector){
        if (element == value) return true;
    }

    return false;
}

/*
 * Callback function to handle response data for CURL requests
 * Parameters:
 * -- contents: pointer to the data received
 * -- size: size of each data element
 * -- nmemb: number of data elements
 * -- userp: pointer to the user-provided data structure
 * Returns:
 * -- size_t: total size of data processed
 */
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

/*
 * Appends a word from a webpage to a file and recursively follows links for more words
 * Parameters:
 * -- curl: CURL session handle
 * -- url: pointer to the URL string
 * -- wordsAddedAlready: pointer to a vector tracking added words
 * -- amountWordsNeeded: pointer to the total number of words needed
 * Returns:
 * -- None
 */
void appendWord(CURL* curl, std::string *url, std::vector<std::string*> *wordsAddedAlready, int *amountWordsNeeded){
    CURLcode res;
    std::string htmlCode;

    // Set the write function to handle the response data
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &htmlCode);

    // Set the URL to fetch
    curl_easy_setopt(curl, CURLOPT_URL, (*url).c_str());

    // Perform the request
    res = curl_easy_perform(curl);

    // Check for errors
    if (res != CURLE_OK) {
        std::cerr << "CURL request failed: " << curl_easy_strerror(res) << std::endl;
    } else {
        std::string fileName = "words.json";
        json wordData = getWordData(htmlCode);

        auto* word = new std::string( wordData["word"] );
        if (!contains(wordsAddedAlready, word)){
            appendToFile(fileName, wordData);
            wordsAddedAlready->push_back(word);

            std::vector<Tag> linksToNewWords = select(htmlCode, wordLinkSelector());
            for (auto link : linksToNewWords){
                if (wordsAddedAlready->size() < *amountWordsNeeded){
                    std::string newUrl = link.getProperty("href");
                    appendWord(curl, &newUrl, wordsAddedAlready, amountWordsNeeded);
                }
                else break;

            }
        }
    }
}

/*
 * Creates a JSON file with words fetched from a starting URL
 * Parameters:
 * -- url: initial URL to fetch words from
 * -- amount: total number of words to collect
 * Returns:
 * -- None
 */
void createWordsFile(std::string url, int amount) {
    CURL* curl;

    // Initialize the CURL session
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // Disable security
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);

        std::vector<std::string*> wordsAdded = {};
        appendWord(curl, &url, &wordsAdded, &amount);

        for (auto* word : wordsAdded){
            delete word;
        }

        // Clean up the CURL session
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}
