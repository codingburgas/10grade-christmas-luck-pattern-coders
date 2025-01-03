//
// Created by Oleksandr Vinichenko on 06.12.2024.
//

//#include "../include/parser.h"
#include "scrapping/scrapper.h"

#include "json.hpp"
using json=nlohmann::json;

int main(int argc, char *argv[]){
    //createWordsFile("https://dictionary.cambridge.org/dictionary/english/game", 1500);
    //createWordsFile("https://dictionary.cambridge.org/dictionary/english/programming", 1000);
    //createWordsFile("https://dictionary.cambridge.org/dictionary/english/lives", 3);
    createWordsFile("https://dictionary.cambridge.org/dictionary/english/master", 1501);

    createWordsFile("https://dictionary.cambridge.org/dictionary/english/creation", 2000);

    createWordsFile("https://dictionary.cambridge.org/dictionary/english/history", 2500);

    createWordsFile("https://dictionary.cambridge.org/dictionary/english/slave", 3000);

    std::cout << "End\n";
}
