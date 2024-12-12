//
// Created by Oleksandr Vinichenko on 06.12.2024.
//

//#include "../include/parser.h"
#include "../include/scrapper.h"

int main(int argc, char *argv[]){
    createWordsFile("https://dictionary.cambridge.org/dictionary/english/degree", 20);
    std::cout << "End\n";
}
