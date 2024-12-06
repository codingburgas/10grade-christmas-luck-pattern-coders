//
// application.h
// Header file, where are declared essential components for interacting with QApplication and QWidget(main window)
//


#ifndef APPLICATION_H
#define APPLICATION_H


#include <iostream>
#include <vector>

#include <QApplication>
#include <QWidget>

#include "algorithms.h"
#include "arrayModificationInfo.h"
#include "notifications.h"


/*
 *Struct, which stores essential objects for application, for convenience
 */
struct APPLICATION{
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
    int run();

    /*
     * Performs an algorithm on array specified by user
     * Parameters:
     * --name: name of the algorithm
     * Returns:
     * --None
     */
    void performAlgorithm(std::string &name);


    /*
     * Updates array on UI(now only prints out changes)
     * Parameters:
     * --changes: reference to a vector, containing vectors, representing changes made in one step(e.g swapping to values would have 2 elements)
     * Returns:
     * --None
     */
    void updateArrayOnUI(std::vector< std::vector<arrayModificationInfo*> > &changes);

    void notify(std::string message, NotificationType type);
};


/*
 * Initializes QApplication, QWidget(used as window) and returns APPLICATION, containing specified objects
 * Parameters:
 * --args: arguments count
 * --argv: stands for "argument vector" and is a pointer to the first string( char array ) out of arguments, which is path to file
 * Returns:
 * --Pointer to an APPLICATION
 */
APPLICATION* init(int argc, char *argv[]);




#endif //APPLICATION_H





