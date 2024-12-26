import QtQuick 2.15

Rectangle{
    id: message
    width: parent.width * 0.44
    height: 80
    anchors.topMargin: 5
    anchors.top: parent.top
    anchors.horizontalCenter: parent.horizontalCenter

    radius: 10


    property string title;
    property string description;
    property string type;

    property int typeId: defineTypeId()


    color: (typeId == 0) ? ("#B2FFB7") : ((typeId == 1) ? ("#FFDEC4") : ("#FFB5B5"))

    function defineTypeId(){
        if (type == "success"){ return 0; }
        if (type == "warning"){ return 1; }
        if (type == "error"){ return 2; }
    }




    Text{
        id: title
        anchors.left: message.left
        anchors.right: message.right
        anchors.top: message.top
        anchors.topMargin: 8
        anchors.leftMargin: 8
        anchors.rightMargin: 8
        height: 20

        text: message.title
        color: (typeId == 0) ? ("#068722") : ((typeId == 1) ? ("#E37200") : ("#CD0000"))

        font.family: "Inter"
        font.weight: 600
        font.pixelSize: 20
    }

    Rectangle{
        id: line
        //border.width: 1
        //border.color: (typeId == 0) ? ("#068722") : ((typeId == 1) ? ("#E37200") : ("#CD0000"))


        anchors.left: message.left
        anchors.right: message.right
        anchors.top: title.bottom
        anchors.topMargin: 8
        anchors.leftMargin: 8
        anchors.rightMargin: 8

        height: 1

        color: (typeId == 0) ? ("#068722") : ((typeId == 1) ? ("#E37200") : ("#CD0000"))

    }

    Text{
        anchors.left: message.left
        anchors.right: message.right
        anchors.top: line.bottom
        anchors.margins: 8
        anchors.bottom: message.bottom


        text: message.description
        color: (typeId == 0) ? ("#068722") : ((typeId == 1) ? ("#E37200") : ("#CD0000"))

        font.family: "Inter"
        font.weight: 300
        font.pixelSize: 14
    }



}
