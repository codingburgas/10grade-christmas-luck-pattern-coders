//
// Created by Oleksandr Vinichenko on 06.12.2024.
//

//#include "../include/parser.h"
#include "scrapping/scrapper.h"

int main(int argc, char *argv[]){
    createWordsFile("https://dictionary.cambridge.org/dictionary/english/game", 20);
    std::cout << "End\n";
}
