//
// api.h
// Header file, where functions for interacting between backend and frontend
//



#ifndef API_H
#define API_H



#include <iostream>
#include <vector>
#include <string>


/*
 * Converts user input to vector of ints
 * Parameters:
 * --userInput: reference to string, containing user input
 * Returns:
 * --vector of ints
 */
std::vector<int> userInputToVector(std::string &userInput){
    try {
        std::vector<int> result = {};

        if (userInput.empty()) { throw 1; } // check if input is empty


        size_t commaPosition = userInput.find(',');
        int first_number; //find first number separately, so that algorithm would be easier for the rest of the string
        try {
            first_number = std::stoi( userInput.substr(0, commaPosition) );
        }
        catch (const std::invalid_argument& e) { throw 2; } // throw error code
        catch (const std::out_of_range& e) { throw 2; }

        result.push_back(first_number);


        while (commaPosition != std::string::npos){

            size_t nextCommaPosition = userInput.find(',', commaPosition+1);
            int number;
            try {
                // convert to int a slice from char after comma until the char before the next comma
                number = std::stoi( userInput.substr(commaPosition+1, nextCommaPosition-commaPosition) );
            }
            catch (const std::invalid_argument& e) { throw 2; } // throw error code
            catch (const std::out_of_range& e) { throw 2; }

            result.push_back(number);

            commaPosition = nextCommaPosition;
        }

        return result;

    } catch (int errorCode){

        switch (errorCode) {
        case 1: {
            std::cerr << "Input is either blank\n";
            break;
        }
        case 2: {
            std::cerr << "Input is invalid\n";
            break;
        }
        default: {
            std::cerr << "Unknown error\n";
            break;
        };
        }

        std::vector<int> blankVector = {};
        return blankVector;
    }


}



/*
 *A structure for tracking array changes
 */
struct arrayModificationInfo{
    size_t elementIndex;
    size_t movedTo;
};


#endif // API_H
