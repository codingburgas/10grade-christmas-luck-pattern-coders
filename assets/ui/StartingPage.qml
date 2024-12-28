import QtQuick 2.15

import QtQuick 6.0
import QtQuick.Controls 6.0
import WordUi 1.0
import TagsUi 1.0

Rectangle{
    id: mainPage
    //anchors.margins: 10
    anchors.centerIn: parent
    width: mainWindow.width// - 2*anchors.margins
    height: mainWindow.height// - 2*anchors.margins

    color: "#182129"


    Rectangle {
        width:300
        height: 250
        anchors.topMargin: 418
        color: "transparent"
        color : "#800000FF"
        radius: 50
        anchors.centerIn: parent
    }

}

