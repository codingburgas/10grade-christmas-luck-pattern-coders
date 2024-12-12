#include <iostream>
#include <fstream>

#include "../include/fileManager.h"
#include "json.hpp"
using json=nlohmann::json;


// Function to append text to a file
void appendToFile(const std::string& fileName, const json& jsonToAppend) {
    json data;
    std::ifstream fileInReadMode(fileName);

    //read exisiting data
    try {
        fileInReadMode >> data;
    } catch (const std::exception& e) {
        std::cerr << "Error reading JSON file: " << e.what() << std::endl;
    }
    fileInReadMode.close();


    // Check if the existing data is an array, if not, convert it to an array
    if (!data.is_array()) {
        json temp = data;
        data = json::array();
        data.push_back(temp);
    }
    data.push_back(jsonToAppend);


    // write to file
    std::ofstream fileInWriteMode(fileName);
    try{
        fileInWriteMode << data;
    } catch (const std::exception& e) {
        std::cerr << "Error writing JSON to file: " << e.what() << std::endl;
    }
}
