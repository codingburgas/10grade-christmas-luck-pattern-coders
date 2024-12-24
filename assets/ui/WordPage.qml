import QtQuick 2.15
import WordUi 1.0

Rectangle{
    id: wordPage
    anchors.margins: 10
    anchors.centerIn: parent
    width: mainWindow.width - 2*anchors.margins
    height: mainWindow.height - 2*anchors.margins


    signal screenChanged(path: string)

    property WordUi word: application.wordsUi[application.indexOfClickedWord]

    //property int tagsSize: application.getTagsUiSize()


    Rectangle{
        id: title
        width: parent.width
        height: 50
        anchors.top: wordPage.top
        Text{
            id: word
            anchors.fill: parent
            text: wordPage.word.word
            font.pointSize: 20
        }
    }

    Repeater{
        id: wordTagsRepeater
        //anchors.top: title.bottom
        model: wordPage.word.getTagsSize()

        Text{
            required property int index
            y: 100 + index*100
            height: 50
            text: wordPage.word.tags[index]
        }
    }

    Repeater{
        id: difficultyTagsRepeater
        //anchors.top: title.bottom
        model: application.tagsUi.getDifficultyTagsSize()

        Text{
            required property int index
            x: 100 + index*100
            y: 50
            text: application.tagsUi.difficultyTags[index]
        }
    }

    Repeater{
        id: partOfSpeechTagsRepeater
        //anchors.top: title.bottom
        model: application.tagsUi.getPartOfSpeechTagsSize()

        Text{
            required property int index
            x: 100 + index*100
            y: 100
            text: application.tagsUi.partOfSpeechTags[index]
        }
    }

    Repeater{
        id: customTagsRepeater
        //anchors.top: title.bottom
        model: application.tagsUi.getCustomTagsSize()

        Text{
            required property int index
            x: 100 + index*100
            y: 150
            text: application.tagsUi.customTags[index]
        }
    }




    MouseArea{
        anchors.fill: parent

        onClicked: {
            application.message(word.text, "description of the message", "type");
        }
    }




    /*
    Connections{
        target: application

        function onTagsUiChanged(){
            wordPage.tagsSize = application.getDisplayedTagsSize();
        }
    }
    */

    Connections{
        target: wordPage.word

        function onTagsChanged(){
            //wordPage.tagsSize = application.getDisplayedTagsSize();
            wordTagsRepeater.model = wordPage.word.getTagsSize()
        }
    }




}
