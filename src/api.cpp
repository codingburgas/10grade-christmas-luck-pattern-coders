//
// api.cpp
// C++ file, where components, neccessary for communication between frontend and backend, are implemented
//


#include "../include/api.h"
#include "../include/application.h"
#include "../include/notifications.h"




/*
 * Converts user input to vector of ints
 * Parameters:
 * --userInput: reference to string, containing user input
 * Returns:
 * --vector of ints
 */
std::vector<int> userInputToVector(APPLICATION *app, std::string &userInput) {
    try {
        std::vector<int> result = {};

        if (userInput.empty()) {
            throw 1;
        } // Check if input is empty

        size_t commaPosition = userInput.find(',');
        int first_number; // Find first number separately
        try {
            first_number = std::stoi(userInput.substr(0, commaPosition));
        } catch (const std::invalid_argument &e) {
            throw 2; // Throw error code
        } catch (const std::out_of_range &e) {
            throw 2;
        }

        result.push_back(first_number);

        while (commaPosition != std::string::npos) {
            size_t nextCommaPosition = userInput.find(',', commaPosition + 1);
            int number;
            try {
                // Convert to int a slice from char after comma until the char before the next comma
                number = std::stoi(userInput.substr(commaPosition + 1, nextCommaPosition - commaPosition));
            } catch (const std::invalid_argument &e) {
                throw 2; // Throw error code
            } catch (const std::out_of_range &e) {
                throw 2;
            }

            result.push_back(number);

            commaPosition = nextCommaPosition;
        }

        return result;

    } catch (int errorCode) {

        switch (errorCode) {
        case 1: {
            app->notify("Input is blank", NotificationType::ERROR);
            break;
        }
        case 2: {
            app->notify("Input is invalid", NotificationType::ERROR);
            break;
        }
        default: {
            app->notify("Unknown error", NotificationType::ERROR);
            break;
        };
        }

        return {};
    }
}
