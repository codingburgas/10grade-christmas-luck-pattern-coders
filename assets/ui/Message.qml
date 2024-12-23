import QtQuick 2.15

Rectangle{
    id: message
    width: 200
    height: 70
    anchors.topMargin: 5
    anchors.top: parent.top
    anchors.horizontalCenter: parent.horizontalCenter

    property string title;
    property string description;
    property string type;

    Text{
        anchors.left: message.left
        anchors.top: message.top
        text: message.title
    }

    Text{
        anchors.left: message.left
        anchors.verticalCenter: message.verticalCenter
        text: message.description
    }

    Text{
        anchors.left: message.left
        anchors.bottom: message.bottom
        text: message.type
    }


}
