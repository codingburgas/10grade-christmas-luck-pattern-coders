//
// fileManager.h
// Header file with functions, which interact with files
//


#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "json.hpp"
using json=nlohmann::json;


/*
 * Appends JSON data to an existing file.
 * Parameters:
 * --fileName: Path to the file where JSON data is appended.
 * --jsonToAppend: The JSON data to be appended to the file.
 * Returns:
 * --None
 */
void appendToFile(const std::string& fileName, const json& jsonToAppend);



/*
 * Writes JSON data to a specified file.
 * Parameters:
 * -- data: the JSON object to write to the file.
 * -- fileName: the path to the file where the JSON data should be saved.
 * Returns:
 * -- No return value. If an error occurs during the writing process, a Message exception is thrown.
 */
void writeJsonToFile(const json& data, const std::string& fileName);



/*
 * Reads JSON data, saved in the file
 * Parameters:
 * --fileName: path to a file from which JSON data is read.
 * Returns:
 * --data as json
 */
json getJsonDataFromFile(const std::string& fileName);





#endif // FILEMANAGER_H
