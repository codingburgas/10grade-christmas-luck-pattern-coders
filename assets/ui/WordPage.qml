import QtQuick 2.15

Rectangle{
    id: wordPage
    anchors.margins: 10
    anchors.centerIn: parent
    width: mainWindow.width - 2*anchors.margins
    height: mainWindow.height - 2*anchors.margins


    signal screenChanged(path: string)
    property int index: application.indexOfClickedWord

    Rectangle{
        anchors.fill: parent
        Text{
            anchors.fill: parent
            text: application.displayedWords[wordPage.index][0]
            font.pointSize: 30
        }
    }



}
