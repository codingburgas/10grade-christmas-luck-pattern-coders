pragma ComponentBehavior: Bound

import QtQuick 2.15
import QtQuick.Effects



Rectangle{
    /*
    Properties to be set:
        string tagName: name to be displayed
        int removeFrom: 0 - no remove button; 1 - from chosen tags; 2 - from word
        int addTo: 0 - no ability to add; 1 -to chosen tags; 2 - to word
    */

    id: tag
    width: 80
    height: 30
    radius: 45
    color: "#0099D1"






    /*property string tagText: (() => {
                                 if (!chosen){
                                     return application.tagsUi.getElementOnIndex(index);
                                 }

                                 if (location == 0){
                                     return application.tagsChosenUi[index];
                                 } else if (location == 1){
                                     return application.wordsUi[application.indexOfClickedWord].tags[index];
                                 } else{
                                     application.message("Unexpected type of tag");
                                 }

                             })()*/


    /*function defineVisible() {
        if (chosen){
            return true;
        }
        if (location == 0){
            return !application.isInTagsChosen(tagText)
        } else{
            return (!application.wordsUi[application.indexOfClickedWord].isInTags(tagText) && application.tagsUi.isInCustomTags(tagText))
        }
    }

    visible: defineVisible()*/

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
            } else{
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



    /*Connections{
        target: application

        function onTagsChosenUiChanged(){
            tag.visible = tag.defineVisible()
            removeButton.visible = removeButton.defineVisible()
        }

    }*/

    /*Connections{
        target: application.wordsUi[application.indexOfClickedWord]

        function onTagsChanged(){
            tag.visible = tag.defineVisible()
            removeButton.visible = removeButton.defineVisible()
        }
    }*/
}
