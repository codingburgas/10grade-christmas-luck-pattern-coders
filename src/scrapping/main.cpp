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
    // createWordsFile("https://dictionary.cambridge.org/dictionary/english/master", 1501);

    // createWordsFile("https://dictionary.cambridge.org/dictionary/english/creation", 3000);

    // createWordsFile("https://dictionary.cambridge.org/dictionary/english/history", 4000);

    // createWordsFile("https://dictionary.cambridge.org/dictionary/english/slave", 5000);

    // createWordsFile("https://dictionary.cambridge.org/dictionary/english/expression", 6000);

    // createWordsFile("https://dictionary.cambridge.org/dictionary/english/determine", 7000);

    // createWordsFile("https://dictionary.cambridge.org/dictionary/english/external", 8000);

    // createWordsFile("https://dictionary.cambridge.org/dictionary/english/epidural", 9000);

    // createWordsFile("https://dictionary.cambridge.org/dictionary/english/restriction", 10000);

    // createWordsFile("https://dictionary.cambridge.org/dictionary/english/equivalent", 12000);

    // createWordsFile("https://dictionary.cambridge.org/dictionary/english/recommendation", 14000);

    // createWordsFile("https://dictionary.cambridge.org/dictionary/english/independence", 16000);

    // createWordsFile("https://dictionary.cambridge.org/dictionary/english/home-rule", 18000);

    createWordsFile("https://dictionary.cambridge.org/dictionary/english/advancement", 20000);
    std::cout << "End\n";
}
