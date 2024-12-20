#include <iostream>
#include "testFunctions.h"

int main(){
    bool failed = false;


    /*{
        std::cout << "----Testing getTagData-----------\n";
        int code = test_getTagData();
        printResult(code);

        std::cout << "---------------------------------\n";
    }*/



    /*{
        std::cout << "----Testing select-----------\n";
        int code = test_select()();
        printResult(code);

        std::cout << "---------------------------------\n";
    }*/





    {
        std::cout << "----Testing sortWords-----------\n";
        int code = test_sortWords();
        printResult(code, &failed);

        std::cout << "---------------------------------\n";
    }




    {
        std::cout << "----Testing leaveWordsWithSpecificPart-----------\n";
        int code = test_leaveWordsWithSpecificPart();
        printResult(code, &failed);

        std::cout << "---------------------------------\n";
    }


    if (failed){
        std::cout << "\n\nProgram works not as intended\n\n";
    } else{
        std::cout << "\n\nProgram is ready to run\n\n";
    }

    return failed;
}
