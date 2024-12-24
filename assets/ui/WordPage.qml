import QtQuick 2.15
import WordUi 1.0

Rectangle{
    id: wordPage
    anchors.margins: 10
    anchors.centerIn: parent
    width: mainWindow.width - 2*anchors.margins
    height: mainWindow.height - 2*anchors.margins


    signal screenChanged(path: string)

    property WordUi word: application.displayedWords[application.indexOfClickedWord]

    property int tagsSize: application.getDisplayedTagsSize()


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
        id: tagsRepeater
        anchors.top: title.bottom
        model: wordPage.word.getTagsSize()

        Text{
            y: 100 + index*50
            height: 50
            required property int index
            text: wordPage.word.tags[index]
        }
    }




    MouseArea{
        anchors.fill: parent

        onClicked: {
            application.message(word.text, "description of the message", "type");
        }
    }





    Connections{
        target: application

        function onDisplayedTagsChanged(){
            wordPage.tagsSize = application.getDisplayedTagsSize();
        }
    }

    Connections{
        target: wordPage.word

        function onTagsChanged(){
            //wordPage.tagsSize = application.getDisplayedTagsSize();
            tagsRepeater.model = wordPage.word.getTagsSize()
        }
    }




}
