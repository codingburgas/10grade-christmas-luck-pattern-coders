import QtQuick 2.15

import QtQuick 6.0
import QtQuick.Controls 6.0
import WordUi 1.0
import TagsUi 1.0

Rectangle{
    id: mainPage
    //anchors.margins: 10
    anchors.centerIn: parent
    width: mainWindow.width
    height: mainWindow.height

    color: "#182129"
    signal screenChanged(path:string)

    Rectangle {
        id: rectangle
        width:parent.width*0.40
        height:parent.height*0.20
        color: Qt.rgba(132, 132, 132, 0.8)
        radius: 50
        anchors.centerIn: parent

        Text {
            id: expandYourWords
            text: "Expand Your Words,"
            font.pixelSize: mainPage.height*0.05
            color: "#347BBD"
            anchors.centerIn: parent
            anchors.verticalCenterOffset: -30
        }

        Text {
            text: "Empower Your World."
            font.pixelSize: mainPage.height*0.05
            color: "#347BBD"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: expandYourWords.bottom
        }
    }


    Text {
        text: "Lexlfy"
        font.pixelSize: 100
        color: "#347BBD"
        anchors.centerIn: parent
        anchors.verticalCenterOffset: -200
    }

    Rectangle {
        width:parent.width*0.4
        height:100
        anchors.centerIn: parent
        anchors.verticalCenterOffset: 180
        color: Qt.rgba(132, 132, 132, 0.8)
        radius: 50

        Text{
            id:getStarted
            text:"Get Started"
            font.pixelSize: mainPage.height*0.065
            color: "#182129"
            anchors.centerIn: parent

        }

        MouseArea {
            anchors.fill: parent
            onClicked:{
                mainPage.screenChanged("MainPage.qml")
            }
        }
    }

    Image {
        id: vocBookAvatar
        source: "qrc:/VocabBook.png"
        width:40
        height:40
        anchors.centerIn: parent
        anchors.verticalCenterOffset: -260
        anchors.horizontalCenterOffset: 32
    }



}
