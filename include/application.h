//
// Created by Oleksandr Vinichenko on 05.12.2024.
//

#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>

#include <QApplication>
#include <QWidget>
#include <QFile>
#include <QUiLoader>



/*
 *Struct, which stores essential objects for application, for convenience
 */
struct APPLICATION {
    QApplication *app;
    QWidget *window;
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




/*
 * Runs an application
 * Parameters:
 * --app: APPLICATION, which operations are directed to
 * Returns:
 * --status code
 */
int run(APPLICATION *app){
    app->window->show();

    int code =  app->app->exec();

    switch (code) {
    case 0:
        std::cout << "Application exited successfully! \n";
        break;
    default:
        std::cerr << "Unknown error occured. \n";
        break;
    }

    return code;
}
