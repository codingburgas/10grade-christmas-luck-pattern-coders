//
// application.h
// Header file, where are declared essential components for interacting with QApplication and QWidget(main window)
//

#ifndef APPLICATION_H
#define APPLICATION_H


#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QFile>
#include <QUiLoader>
#include <QString>

#include "algorithms.h"
#include "api.h"



/*
 *Struct, which stores essential objects for application, for convenience
 */
struct APPLICATION {

    QApplication *app;
    QWidget *window;
    std::vector<int> arrayToBeSorted;


    /*
     * Runs an application
     * Parameters:
     * --None
     * Returns:
     * --status code
     */
    int run(){
        window->show();

        int code =  app->exec();

        switch (code) {
        case 0:
            std::cout << "Application exited successfully! \n";
            break;
        default:
            std::cout << "Unknown error occured. \n";
            break;
        }

        return code;
    }




    /*
     * Performs an algorithm on array specified by user
     * Parameters:
     * --name: name of the algorithm
     * Returns:
     * --None
     */
    void performAlgorithm(std::string &name){

        if (name == "bubbleSort"){
            auto changes = SORTING::bubbleSort(arrayToBeSorted);
            updateArrayOnUI(changes);
        } else{
            std::cerr << "Unknown algorithm. \n";
        }
    }



    /*
     * Updates array on UI(now only prints out changes)
     * Parameters:
     * --changes: reference to a vector, containing vectors, representing changes made in one step(e.g swapping to values would have 2 elements)
     * Returns:
     * --None
     */
    void updateArrayOnUI(std::vector< std::vector<arrayModificationInfo*> > &changes){
        // DO STUFF
        for (size_t i=0; i<changes.size(); i++){
            for (size_t j=0; j<changes[i].size(); j++){
                std::cout << "Element on " << changes[i][j]->elementIndex << " to " << changes[i][j]->movedTo << "\n";
            }
            std::cout << "---------------------------------\n";
        }
    }
};


/*
 * Initializes QApplication, QWidget(used as window) and returns APPLICATION, containing specified objects
 * Parameters:
 * --args: arguments count
 * --argv: stands for "argument vector" and is a pointer to the first string( char array ) out of arguments, which is path to file
 * Returns:
 * --Pointer to an APPLICATION
 */
APPLICATION* init(int argc, char *argv[]){

    auto *app = new QApplication(argc, argv);


    //open file with ui
    QFile file(":/main.ui");
    file.open(QFile::ReadOnly);

    QUiLoader loader;
    QWidget *window = loader.load(&file);
    file.close();


    auto *application = new APPLICATION{
        app,
        window
    };

    return application;
}




#endif //APPLICATION_H





