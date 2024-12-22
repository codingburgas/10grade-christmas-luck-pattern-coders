import QtQuick 2.15
import QtQuick.Layouts
//import QtQuick.Controls 2.15

Window {
    visible: true
    width: 640
    height: 480
    title: "Hello, " + application.test

    /*Rectangle{
        width: 300
        height: 300
        color: "#ff0000"

        Text{
            text: application.displayedWords[index]

        }
    }*/
    ColumnLayout{
        Repeater{
            model: application.displayedWords

            WordRectangle{
                required property int index

                property string word: application.displayedWords[index][0]
                property string definition: application.displayedWords[index][1]
                property string partOfSpeech: application.displayedWords[index][2]
                property string difficulty: application.displayedWords[index][3]
                property string url: application.displayedWords[index][4]
                property string frequencyOfUse: application.displayedWords[index][5]
            }
        }
    }




}
