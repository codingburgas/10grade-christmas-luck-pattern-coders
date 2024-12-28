pragma ComponentBehavior: Bound

import QtQuick 2.15
import QtQuick.Layouts 2.15
import QtQuick.Controls 2.15

Window {
    id: mainWindow
    visible: true
    width: 800
    height: 600

    minimumWidth: 700
    minimumHeight: 600
    /*width: 1536
    height: 801

    onWidthChanged: {
        console.log(`${width}x${height}`)
    }*/
    //visibility: Qt.WindowFullScreen
    //minimumWidth: width
    //minimumHeight: height

    title: "LEXIFY"

    property int userWasOnPage: 1

    property string currentPath: "MainPage.qml"
    property Rectangle currentPage



    Component.onCompleted: {
        currentPage = Qt.createComponent( Qt.resolvedUrl(currentPath) ).createObject(mainWindow, {x:0, y:0})
    }


    Connections{
        target: mainWindow.currentPage
        //checks if user clicked sth, which is supposed to enter new page
        function onScreenChanged(path){

            if (mainWindow.currentPath != path){
                //create new component from path given and convert it into object
                let newComponent = Qt.createComponent( Qt.resolvedUrl(path) )

                let changeWindow = () => {
                    if (newComponent.status == Component.Ready){

                        let newPage = newComponent.createObject(mainWindow, {x:0, y:0})
                        mainWindow.currentPage.destroy()
                        mainWindow.currentPage = newPage
                        mainWindow.currentPath = path

                    } else if (newComponent.status == Component.Error){
                        console.log("Error while switching screens: ", newComponent.errorString());
                    }


                };


                let waitFunction = () => {
                    if (newComponent.status == Component.Ready){
                        changeWindow();
                    }else if (newComponent.status === Component.Loading) {
                        newComponent.statusChanged.connect(changeWindow); // Connect to statusChanged if still loading
                    } else if (newComponent.status === Component.Error) {
                        application.message("Failed to load new page", `Failed to go to the ${path}`, "error");
                    }
                }


                waitFunction();



            }

        }


    }


    Connections{
        target: application

        function onMessage(title, description, type){
            let messageComponent = Qt.createComponent( Qt.resolvedUrl("Message.qml") )


            let waitFunction = () => {
                if (messageComponent.status == Component.Ready){
                    let message = messageComponent.createObject(
                        mainWindow,
                        {
                            title: title,
                            description: description,
                            type: type
                        });

                    message.destroy(2000)
                }else if (newComponent.status === Component.Loading) {
                    newComponent.statusChanged.connect(changeWindow); // Connect to statusChanged if still loading
                } else if (newComponent.status === Component.Error) {
                    //console.error("Error loading component:", newComponent.errorString()); // Handle error case
                    //application.message("Failed to create message", `Failed to go to the ${page}`, "error");
                }
            }


            waitFunction();
        }
    }


}
