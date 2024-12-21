#ifndef SCRAPPER_H
#define SCRAPPER_H

#include <iostream>


/*
 * Creates a JSON file with words fetched from a starting URL
 * Parameters:
 * -- url: initial URL to fetch words from
 * -- amount: total number of words to collect
 * Returns:
 * -- None
 */
void createWordsFile(std::string url, int amount);


#endif // SCRAPPER_H
