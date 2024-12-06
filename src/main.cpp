//
// main.cpp
// C++ file for the main program
//




#include "../include/application.h"



int main(int argc, char *argv[]) {
    APPLICATION *app = init(argc, argv);

    return app->run();
}
