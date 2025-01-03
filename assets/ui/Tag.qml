pragma ComponentBehavior: Bound

import QtQuick 2.15
import QtQuick.Effects



Rectangle{
    id: tag
    width: 80
    height: 30
    radius: 45
    color: "#0099D1"

    Rectangle{
        id: removeButton
        //anchors.verticalCenter: tag.verticalCenter
        anchors.right: tag.right
        anchors.rightMargin: 2
        anchors.topMargin: 2
        anchors.bottomMargin: 2
        anchors.top: tag.top
        anchors.bottom: tag.bottom

        width: height
        radius: 44
        color: "white"
        clip: true



        visible: (tag.removeFrom != 0)


        Image{
            id: crossImg
            source: "qrc:/crossToClose.png"
            anchors.fill: parent
            anchors.margins: 6
            fillMode: Image.PreserveAspectCrop
            clip: true
        }

        MouseArea{
            anchors.fill: parent

            onClicked: {

                if (tag.removeFrom == 1){
                    application.removeTagFromChosen(tag.index);
                } else{
                    application.deleteWordTag(application.indexOfClickedWord, tag.index);
                }


            }
        }

    }







    TextEdit{
        id: textField
        width: 50

        height: tag.height
        anchors.left: tag.left
        anchors.leftMargin: 3

        //text: tag.tagText
        text: tag.tagName
        color: "#FFFFFF"
        font.family: "Inter"
        font.weight: 300
        font.pixelSize: 15
        //horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter

        Component.onCompleted: {
            anchors.right = undefined
            if (tag.removeFrom != 0){
                anchors.right = removeButton.left
            } else if (tag.deleteButton) {
                anchors.right = deleteButton.left
            }else{
                anchors.right = tag.right
            }

            this.text = elidedText()
        }

        readOnly: true
        selectByMouse: true
        selectedTextColor: "#ffffff"
        selectionColor: "#5969c9"


        function elidedText(){
            let position = 0
            let elide = true;

            while(true){
                let rect = this.positionToRectangle(position)
                let text = this.text.substring(position, 1)
                if (rect.x > this.width || rect.y > this.height){
                    break;
                }

                if (position >= this.text.length){
                    elide = false;
                    break;
                }

                position++;
            }

            if (elide){
                return this.text.substring(0, position-3) + "..."
            } else{
                return this.text
            }


        }
    }



    MouseArea{
        visible: (tag.addTo != 0)
        anchors.fill: parent

        onClicked: {
            if (tag.addTo == 1){
                application.addTagToChosen(tag.index)
            } else{
                application.addWordTag(application.indexOfClickedWord, tag.index)
            }


        }
    }


    Rectangle{
        id: deleteButton
        anchors.right: tag.right
        anchors.rightMargin: 2
        anchors.topMargin: 2
        anchors.bottomMargin: 2
        anchors.top: tag.top
        anchors.bottom: tag.bottom

        width: height
        radius: 44
        color: "white"
        clip: true



        visible: tag.deleteButton


        Image{
            id: deleteImg
            source: "qrc:/trashCan.png"
            anchors.fill: parent
            anchors.margins: 2
            fillMode: Image.PreserveAspectCrop
            clip: true
        }

        MouseArea{
            anchors.fill: parent

            onClicked: {
                application.deleteTag(tag.index)
            }
        }

    }
}
