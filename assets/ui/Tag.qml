import QtQuick 2.15

Rectangle{
    id: tag
    width: 50
    height: 30
    border.width: 2

    //property int index

    //property bool chosen

    property string tagText: (chosen) ? (application.tagsChosenUi[index]) : (application.tagsUi.getElementOnIndex(index))
    visible: (chosen) ? (true) : (!application.isInTagsChosen(application.tagsUi.getElementOnIndex(index)))


    Text{
        id: text
        width: 30
        anchors.left: tag.left

        text: tag.tagText
    }

    Rectangle{
        id: removeButton
        //anchors.left: text.right
        //anchors.right: tag.right
        //anchors.bottom: tag.bottom
        anchors.fill: parent

        visible: tag.chosen

        Text{
            text: "✖"
            anchors.fill: parent
            visible: removeButton.visible


        }

        MouseArea{
            anchors.fill: parent
            //z: 3

            onClicked: {
                application.removeTagFromChosen(tag.index);
            }
        }


    }

    MouseArea{
        visible: !chosen
        //enabled: !removeButton.visible
        anchors.fill: parent

        onClicked: {
            application.addTagToChosen(tag.index)
        }
    }


    Connections{
        target: application

        function onTagsChosenUiChanged(){
            tag.visible = (tag.chosen) ? (true) : (!application.isInTagsChosen(application.tagsUi.getElementOnIndex(tag.index)))
        }
    }
}
