
#include <iostream>
#include <vector>
#include <fstream>
#include <curl/curl.h>

#include "../include/scrapper.h"
#include "../include/parser.h"




// Function to append text to a file
void appendToFile(const std::string& fileName, const std::string& textToAppend) {
    // Open the file in append mode
    std::ofstream outFile(fileName, std::ios::app);


    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open file: " << fileName << std::endl;
        return;
    }

    // Append the text to the file
    outFile << textToAppend << std::endl;

    outFile.close();

}





// Callback function to write the response data into a string
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}




void appendWord(CURL* curl, std::string &url){
    CURLcode res;
    std::string htmlCode;

    // Set the write function to handle the response data
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &htmlCode);

    // Set the URL to fetch
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());


    // Perform the request
    res = curl_easy_perform(curl);

    // Check for errors
    if (res != CURLE_OK) {
        std::cerr << "CURL request failed: " << curl_easy_strerror(res) << std::endl;
    } else {
        std::string fileName = "words.txt";
        std::string wordData = getWordData(htmlCode);
        appendToFile(fileName, wordData);
    }

}




// Function to fetch a web page
void createWordsFile(std::string url) {
    CURL* curl;


    // Initialize the CURL session
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        //disable security
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);




        for (int i=0; i<1; i++){
            appendWord(curl, url);
        }


        // Clean up the CURL session
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

}
