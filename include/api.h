//
// api.h
// Header file, where functions for interacting between backend and frontend
//

#ifndef API_H
#define API_H

#include <iostream>
#include <vector>
#include <string>
#include "application.h"


/*
 * Converts user input to vector of ints
 * Parameters:
 * --userInput: reference to string, containing user input
 * Returns:
 * --vector of ints
 */
std::vector<int> userInputToVector(APPLICATION *app, std::string &userInput);

#endif // API_H
