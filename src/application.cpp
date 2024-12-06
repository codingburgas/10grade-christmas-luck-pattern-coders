
// application.cpp
// C++ file, where are implemented essential components for interacting with QApplication and QWidget(main window)



#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QFile>
#include <QUiLoader>
#include <QString>

#include "../include/application.h"
#include "../include/algorithms.h"
#include "../include/api.h"
#include "../include/arrayModificationInfo.h"
#include "../include/notifications.h"




/*
 * Runs an application
 * Parameters:
 * --None
 * Returns:
 * --status code
 */
int APPLICATION::run(){
    window->show();

    int code = app->exec();

    switch (code) {
    case 0:
        notify("Application exited successfully!", NotificationType::SUCCESS);
        break;
    default:
        notify("Unknown error occured.", NotificationType::UNKNOWN);
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
void APPLICATION::performAlgorithm(std::string &name){

    if (name == "bubbleSort"){
        auto changes = SORTING::bubbleSort(arrayToBeSorted);
        updateArrayOnUI(changes);
    } else{
        notify("Unknown algorithm.", NotificationType::ERROR);
    }
}



/*
 * Updates array on UI(now only prints out changes)
 * Parameters:
 * --changes: reference to a vector, containing vectors, representing changes made in one step(e.g swapping to values would have 2 elements)
 * Returns:
 * --None
 */
void APPLICATION::updateArrayOnUI(std::vector< std::vector<arrayModificationInfo*> > &changes){
    // DO STUFF
    for (size_t i=0; i<changes.size(); i++){
        for (size_t j=0; j<changes[i].size(); j++){
            std::cout << "Element on " << changes[i][j]->elementIndex << " to " << changes[i][j]->movedTo << "\n";
        }
        std::cout << "---------------------------------\n";
    }
}




void APPLICATION::notify(std::string message, NotificationType type){
    switch (type) {
    case NotificationType::SUCCESS:
        std::cout << message << "\n";
        break;
    case NotificationType::ERROR:
        std::cerr << "ERROR:  "<<message << "\n";
        break;
    case NotificationType::UNKNOWN:
        std::cerr << "UNEXPECTED BEHAVIOUR:  " << message << "\n";
        break;
    default:
        break;
    }

}




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
