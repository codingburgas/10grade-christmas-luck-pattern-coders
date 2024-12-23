//
// Created by Oleksandr Vinichenko on 06.12.2024.
//

//#include "../include/parser.h"
#include "scrapping/scrapper.h"

#include "json.hpp"
using json=nlohmann::json;

int main(int argc, char *argv[]){
    createWordsFile("https://dictionary.cambridge.org/dictionary/english/game", 1500);
    //createWordsFile("https://dictionary.cambridge.org/dictionary/english/programming", 1000);
    //createWordsFile("https://dictionary.cambridge.org/dictionary/english/lives", 3);


    std::cout << "End\n";
}
