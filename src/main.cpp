#include "application.h"
#include "fileManager.h"

int main(int argc, char *argv[]) {
    /*Application app;

    return app.run(argc, argv);*/

    std::string fileName = "words.json";
    json data = getJsonDataFromFile(fileName);

    for (json& word : data){
        json tagsArray = json::parse("[]");
        tagsArray.push_back(word["partOfSpeech"]);
        tagsArray.push_back(word["difficulty"]);
        word["tags"] = tagsArray;
    }

    writeJsonToFile(data, fileName);

    return 0;
}
