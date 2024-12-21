//
// Created by Oleksandr Vinichenko on 06.12.2024.
//

//#include "../include/parser.h"
#include "scrapping/scrapper.h"

#include "json.hpp"
using json=nlohmann::json;

int main(int argc, char *argv[]){
    //createWordsFile("https://dictionary.cambridge.org/dictionary/english/game", 10);
    createWordsFile("https://dictionary.cambridge.org/dictionary/english/programming", 15);
    //createWordsFile("https://dictionary.cambridge.org/dictionary/english/lives", 3);


    std::cout << "End\n";
}
