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
            text: word.word
        }
        Text{
            color: "#fffb00"
            text: word.definition
        }
        Text{
            color: "#fffb00"
            text: word.partOfSpeech
        }
        Text{
            color: "#fffb00"
            text: word.difficulty
        }
        Text{
            color: "#fffb00"
            text: word.url
        }
        Text{
            color: "#fffb00"
            text: word.frequencyOfUse
        }
    }

    MouseArea{
        anchors.fill: parent

        onClicked: {
            application.increaseWordFrequncyOfUse(word.indexInDisplayedWords);
        }
    }




}
