import QtQuick 2.15

Rectangle{
    id: tag
    width: 60
    height: 20
    radius: 45
    color: "#0099D1"


    //property int index

    //property bool chosen

    //property int location 0-main page 1-word page
    // property bool chosen

    property string tagText: (() => {
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

                             })()


    function defineVisible() {
        if (chosen){
            return true;
        }
        if (location == 0){
            return !application.isInTagsChosen(tagText)
        } else{
            return (!application.wordsUi[application.indexOfClickedWord].isInTags(tagText) && application.tagsUi.isInCustomTags(tagText))
        }
    }

    visible: defineVisible()


    Text{
        id: textField
        width: 35
        height: tag.height
        anchors.left: tag.left
        anchors.leftMargin: 3

        text: tag.tagText
        elide: Text.ElideRight
        color: "#FFFFFF"
        font.family: "Inter"
        font.weight: 300
        font.pixelSize: 10
        //horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter

    }

    Rectangle{
        id: removeButton
        anchors.left: textField.right
        anchors.verticalCenter: tag.verticalCenter
        anchors.right: tag.right
        anchors.rightMargin: 2
        anchors.topMargin: 2
        anchors.bottomMargin: 2
        anchors.top: tag.top
        anchors.bottom: tag.bottom
        radius: 44
        z: 1000

        function defineVisible(){
            if (!tag.chosen){
                return false;
            }
            if (location == 0){
                return true;
            }
            return application.tagsUi.isInCustomTags(tag.tagText);
        }

        visible: removeButton.defineVisible()

        Image{
            source: "qrc:/crossToClose.png"
            anchors.fill: parent
        }

        MouseArea{
            anchors.fill: parent

            onClicked: {

                if (tag.location == 0){
                    application.removeTagFromChosen(tag.index);
                } else{
                    application.deleteWordTag(application.indexOfClickedWord, tag.index);
                }


            }
        }

    }

    MouseArea{
        visible: !tag.chosen
        anchors.fill: parent

        onClicked: {
            if (tag.location == 0){
                application.addTagToChosen(tag.index)
            } else{
                application.addWordTag(application.indexOfClickedWord, tag.index)
            }


        }
    }



    Connections{
        target: application

        function onTagsChosenUiChanged(){
            //tag.visible = (tag.chosen) ? (true) : (!application.isInTagsChosen(application.tagsUi.getElementOnIndex(tag.index)))
            tag.visible = tag.defineVisible()
            removeButton.visible = removeButton.defineVisible()
        }

    }

    Connections{
        target: application.wordsUi[application.indexOfClickedWord]

        function onTagsChanged(){
            tag.visible = tag.defineVisible()
            removeButton.visible = removeButton.defineVisible()
        }
    }
}
