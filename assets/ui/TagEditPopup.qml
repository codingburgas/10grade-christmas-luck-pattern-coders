pragma ComponentBehavior: Bound

import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts


Rectangle{
    id: tagsEditWindow
    anchors.fill: parent
    color: "#d0000000"

    property int index

    MouseArea{
        anchors.fill: parent
    }



    Rectangle{
        id: mainRect

        width: 610
        height: 400
        color: "#D9D9D9"
        anchors.centerIn: parent

        radius: 30



        ScrollView{
            id: tagsSelectedScrollView
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 8
            height: parent.height * 0.5

            Grid {
                id: tagsSelectedLayout

                width: tagsSelectedScrollView.width
                columnSpacing: 5
                rowSpacing: 5


                columns: 6

                Repeater{
                    id: tagsSelectedRepeater
                    model: (tagsEditWindow.index == 0) ? (application.getTagsChosenUiSize()) : (application.wordsUi[application.indexOfClickedWord].getTagsSize())

                    Tag{
                        //Layout.alignment: Qt.AlignLeft

                        required property int index

                        property string tagName: (tagsEditWindow.index == 0) ? (application.tagsChosenUi[index]) : (application.wordsUi[application.indexOfClickedWord].tags[index])

                        property int removeFrom:
                        (() =>
                            {
                                if (tagsEditWindow.index == 0){
                                    return 1;
                                }

                                if (application.tagsUi.isInCustomTags(tagName)){
                                    return 2;
                                }

                                return 0;
                            }
                        )()

                        property bool deleteButton: false

                        property int addTo: 0
                    }

                    onModelChanged: {
                        tagsSelectedLayout.columns = (tagsSelectedRepeater.model < 6) ? (tagsSelectedRepeater.model):(6)
                    }

                }
            }
        }


        Rectangle{
            id: line
            anchors.top: tagsSelectedScrollView.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 5
            anchors.rightMargin: 5
            height: 2
            color: "#000000"
        }



        ScrollView{
            id: allTagsScrollView
            anchors.top: line.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: 8
            anchors.topMargin: 2




            Grid {
                id: allTagsLayout

                width: allTagsScrollView.width
                columnSpacing: 5
                rowSpacing: 5


                /*columns: {
                    let cols = Math.floor(width / (80 + columnSpacing));
                    return Math.max(cols, 1); // Ensure at least 1 column
                }*/
                columns: 6
                //rows: Math.ceil(allTagsRepeater.model / columns)

                Repeater{
                    id: allTagsRepeater
                    model: application.tagsUi.getDifficultyTagsSize() + application.tagsUi.getPartOfSpeechTagsSize() + application.tagsUi.getCustomTagsSize()

                    Tag{
                        required property int index

                        property string tagName: application.tagsUi.getElementOnIndex(index)

                        property int removeFrom: 0

                        property int addTo: tagsEditWindow.index + 1

                        property bool deleteButton: (tagsEditWindow.index != 0) ? (true) : (application.tagsUi.isInCustomTags(tagName))

                        visible:
                            (() => {
                                if (tagsEditWindow.index == 0){
                                    return !application.isInTagsChosen(application.tagsUi.getElementOnIndex(index));
                                } else{
                                    return !(application.wordsUi[application.indexOfClickedWord].isInTags(tagName) || !application.tagsUi.isInCustomTags(tagName));
                                }
                            }
                            )()
                    }

                }
            }
        }
    }

    Rectangle{
        width: 200
        height: 40
        anchors.bottom: mainRect.top
        anchors.horizontalCenter: parent.horizontalCenter

        anchors.bottomMargin: 30

        TextInput{
            id: newTagInput
            height: parent.height
            width: parent.width - parent.height
            anchors.left: parent.left
            clip: true

            font.pixelSize: 16

            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter

            maximumLength: 40

            Keys.onReturnPressed: {
                application.addTag(text)
                text = ""
            }
        }

        Image{
            source: "qrc:/checkMark.png"
            width: parent.height
            height: width
            anchors.left: newTagInput.right

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    application.addTag(newTagInput.text)
                    text = ""
                }
            }
        }
    }



    Rectangle{
        id: okButton
        color: "#D9D9D9"
        anchors.top: mainRect.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 30
        height:40
        width: 200

        radius: 50

        Text{
            text: "Save"

            anchors.fill: parent
            padding: 6
            font.pointSize: 25
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
        }

        MouseArea{
            anchors.fill: parent

            onClicked: {
                tagsEditWindow.destroy(0);
            }
        }
    }


    /*Component.onCompleted: {
        tagsSelectedRepeater.model = (tagsEditWindow.index == 0) ? (application.getTagsChosenUiSize()) : (application.wordsUi[application.indexOfClickedWord].getTagsSize())
    }*/

    Connections{
        target: application

        function onTagsChosenUiChanged(){
            tagsSelectedRepeater.model = null
            tagsSelectedRepeater.model = (tagsEditWindow.index == 0) ? (application.getTagsChosenUiSize()) : (application.wordsUi[application.indexOfClickedWord].getTagsSize())

            allTagsRepeater.model = null
            allTagsRepeater.model = application.tagsUi.getDifficultyTagsSize() + application.tagsUi.getPartOfSpeechTagsSize() + application.tagsUi.getCustomTagsSize()

        }


        /*function onTagsUiChanged(){
            tagsSelectedRepeater.model = null
            tagsSelectedRepeater.model = (tagsEditWindow.index == 0) ? (application.getTagsChosenUiSize()) : (application.wordsUi[application.indexOfClickedWord].getTagsSize())

            allTagsRepeater.model = null
            allTagsRepeater.model = application.tagsUi.getDifficultyTagsSize() + application.tagsUi.getPartOfSpeechTagsSize() + application.tagsUi.getCustomTagsSize()

        }*/

    }

    /*Connections{
        target: application.wordsUi[application.indexOfClickedWord]

        function onTagsChanged(){
            tagsSelectedRepeater.model = null
            tagsSelectedRepeater.model = (tagsEditWindow.index == 0) ? (application.getTagsChosenUiSize()) : (application.wordsUi[application.indexOfClickedWord].getTagsSize())

            allTagsRepeater.model = null
            allTagsRepeater.model = application.tagsUi.getDifficultyTagsSize() + application.tagsUi.getPartOfSpeechTagsSize() + application.tagsUi.getCustomTagsSize()


        }
    }*/
    Connections{
        target: application

        function onWordTagsChanged(){
            tagsSelectedRepeater.model = null
            tagsSelectedRepeater.model = (tagsEditWindow.index == 0) ? (application.getTagsChosenUiSize()) : (application.wordsUi[application.indexOfClickedWord].getTagsSize())

            allTagsRepeater.model = null
            allTagsRepeater.model = application.tagsUi.getDifficultyTagsSize() + application.tagsUi.getPartOfSpeechTagsSize() + application.tagsUi.getCustomTagsSize()

        }
    }

    Connections{
        target: application.tagsUi

        function onCustomTagsChanged(){
            tagsSelectedRepeater.model = null
            tagsSelectedRepeater.model = (tagsEditWindow.index == 0) ? (application.getTagsChosenUiSize()) : (application.wordsUi[application.indexOfClickedWord].getTagsSize())

            allTagsRepeater.model = null
            allTagsRepeater.model = application.tagsUi.getDifficultyTagsSize() + application.tagsUi.getPartOfSpeechTagsSize() + application.tagsUi.getCustomTagsSize()

        }
    }


}
