//
// fileManager.cpp
// C++ file with functions, which interact with files
//

#include <iostream>
#include <fstream>

#include "fileManager.h"
#include "json.hpp"
using json=nlohmann::json;




/*
 * Reads JSON data, saved in the file
 * Parameters:
 * --fileName: ath to a file from which JSON data is read.
 * Returns:
 * --data as json
 */
json getJsonDataFromFile(const std::string &fileName){
    json result;

    std::ifstream file(fileName);


    try{
        file >> result;
    } catch(...){
        std::cerr << "Json data is either incorrect or blank. It will be replaced with blank array.\n";
    }

    file.close();

    if (result.empty()) result = json::parse("[]");

    return result;
}



/*
 * Appends JSON data to an existing file.
 * Parameters:
 * --fileName: Path to the file where JSON data is appended.
 * --jsonToAppend: The JSON data to be appended to the file.
 * Returns:
 * --None
 */
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
        fileInWriteMode << data.dump(4);
    } catch (const std::exception& e) {
        std::cerr << "Error writing JSON to file: " << e.what() << std::endl;
    }
    fileInWriteMode.close();
}
