//
// fileManager.cpp
// C++ file with functions, which interact with files
//

#include <iostream>
#include <fstream>

#include "fileManager.h"
#include "message.h"
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

    if (!file){
        throw Message("Error while opening file", "Error while opening file", "error");
    }

    if (file.peek() == std::ifstream::traits_type::eof()){
        file.close();
        throw Message("File with data is blank", "Json data is absent. Application will not work correctly.", "error");
    }


    try{
        file >> result;

    } catch(...){
        file.close();
        return json::parse("[]");
    }

    file.close();
    return result;


    /*
    if (result.empty()){
        result = json::parse("[]");
        //throw Message("File with data is blank or incorrect", "Json data is either incorrect or blank. Application will not word correctly.", "error");
    }

    return result;
    */
}


/*
 * Writes JSON data to a specified file.
 * Parameters:
 * -- data: the JSON object to write to the file.
 * -- fileName: the path to the file where the JSON data should be saved.
 * Returns:
 * -- No return value. If an error occurs during the writing process, a Message exception is thrown.
 */
void writeJsonToFile(const json& data, const std::string& fileName){
    std::ofstream file(fileName);
    try{
        file << data.dump(4);
    } catch (const std::exception& e) {
        //std::cerr << "Error writing JSON to file: " << e.what() << std::endl;
        std::string title = "Something went wrong :(";
        std::string description =  "Error writing JSON to file";
        std::string type = "error";

        throw Message(title, description, type);
    }
    file.close();
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
    writeJsonToFile(data, fileName);
}
