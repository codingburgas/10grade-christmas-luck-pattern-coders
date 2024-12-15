//
// fileManager.h
// Header file with functions, which interact with files
//


#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "json.hpp"
using json=nlohmann::json;

void appendToFile(const std::string& fileName, const json& jsonToAppend);



/*
 * Reads JSON data, saved in the file
 * Parameters:
 * --fileName: ath to a file from which JSON data is read.
 * Returns:
 * --data as json
 */
json getJsonDataFromFile(const std::string& fileName);




#endif // FILEMANAGER_H
