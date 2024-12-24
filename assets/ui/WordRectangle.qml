pragma ComponentBehavior: Bound

import QtQuick 2.15
import QtQuick.Layouts

Rectangle {
    id: word
    width: 300
    height: 150


    color: "#00dfff"


    ColumnLayout{
        /*Repeater{
            model: 6
            Text{

                required property int index
                color: "#fffb00"
                text: word.data[index]
            }
        }*/
        Text{
            color: "#fffb00"
            //text: word.word
            text: word.wordUi.word
        }
        Text{
            color: "#fffb00"
            //text: word.definition
            text: word.wordUi.definition
        }
        Text{
            color: "#fffb00"
            //text: word.partOfSpeech
            text: word.wordUi.partOfSpeech
        }
        Text{
            color: "#fffb00"
            //text: word.difficulty
            text: word.wordUi.difficulty
        }
        Text{
            color: "#fffb00"
            //text: word.url
            text: word.wordUi.url
        }
        Text{
            color: "#fffb00"
            //text: word.frequencyOfUse
            text: word.wordUi.frequencyOfUse
        }
        Repeater{
            id: tagsRepeater
            model: wordUi.getTagsSize()

            Text{
                required property int index
                color: "#fffb00"
                //text: word.frequencyOfUse
                text: word.wordUi.tags[index]
            }
        }
    }

    MouseArea{
        anchors.fill: parent

        onClicked: {
            application.increaseWordFrequncyOfUse(word.indexInDisplayedWords);
            application.indexOfClickedWord = word.indexInDisplayedWords;
            word.page.screenChanged("WordPage.qml");
        }
    }



    Connections{
        target: word.wordUi

        function onTagsChanged(){
            tagsRepeater.model = word.wordUi.getTagsSize();
        }
    }



}
