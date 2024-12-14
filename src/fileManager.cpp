#include <iostream>
#include <fstream>

#include "fileManager.h"
#include "json.hpp"
using json=nlohmann::json;




json getJsonDataFromFile(const std::string &fileName){
    json result;

    std::ifstream file(fileName);


    try{
        file >> result;
    } catch(std::exception &e){
        std::cerr << "Failed to read from the file.\n";
    }

    file.close();

    return result;
}



// Function to append text to a file
void appendToFile(const std::string& fileName, const json& jsonToAppend) {
    json data = getJsonDataFromFile(fileName);


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
    fileInWriteMode.close();
}
