#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "json.hpp"
using json=nlohmann::json;

void appendToFile(const std::string& fileName, const json& jsonToAppend);

json getJsonDataFromFile(const std::string& fileName);




#endif // FILEMANAGER_H
