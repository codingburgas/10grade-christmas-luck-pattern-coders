pragma ComponentBehavior: Bound

import QtQuick 2.15
import QtQuick.Layouts 2.15
import QtQuick.Controls 2.15

Window {
    id: mainWindow
    visible: true
    width: 800
    height: 600
    title: "LEXIFY"


    property string currentPath: "MainPage.qml"
    property Rectangle currentPage: MainPage{}



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
                        console.error("Error loading component:", newComponent.errorString()); // Handle error case
                    }
                }


                waitFunction();



            }

        }

    }


}
