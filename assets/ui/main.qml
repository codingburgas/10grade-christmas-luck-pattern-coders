pragma ComponentBehavior: Bound

import QtQuick 2.15
import QtQuick.Layouts 2.15
//import QtQuick.Controls 2.15

Window {
    id: mainWindow
    visible: true
    width: 800
    height: 600
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
        id: mainPart
        anchors.margins: 10
        anchors.centerIn: parent
        width: mainWindow.width - 2*anchors.margins
        height: mainWindow.height - 2*anchors.margins

        Rectangle{
            //width: 400
            //height: 50
            Layout.fillWidth: true
            Row{
                anchors.fill: parent
                spacing: 5

                Rectangle{
                    width: 400
                    height: 50
                    border.width: 3

                    TextInput{
                        id: searchInput
                        anchors.fill: parent
                        font.pointSize: 18
                        text: "hi"

                    }
                }



                Rectangle{
                    id: searchButton
                    width: 50
                    height: 50
                    border.width: 3

                    MouseArea{
                        anchors.fill: parent

                        onClicked: {
                            var propertyName = "word";
                            application.searchWords(searchInput.text, propertyName);
                        }
                    }
                }
            }
        }






        Rectangle{
            id: content
            //anchors.margins: 10
            Layout.fillWidth: true
            //Layout.fillHeight: true
            //width: mainWindow.width - 2*anchors.margins
            //height: mainWindow.height - 2*anchors.margins

            //anchors.centerIn: parent


            property int displayedWordsSize: application.getDisplayedWordsSize()
            property int wordRectWidth: 305
            property int wordsPerRow: content.width / content.wordRectWidth
            //property int rowsAmount: displayedWordsSize / wordsPerRow
            //property int wordsPerRow: (content.width % content.wordRectWidth == 0) ? (content.width / content.wordRectWidth) : ((content.width / content.wordRectWidth) + 1)
            property int rowsAmount: (displayedWordsSize % wordsPerRow == 0) ? (displayedWordsSize / wordsPerRow) : ((displayedWordsSize / wordsPerRow) + 1)


            ColumnLayout{
                id: columnLayout
                anchors.fill: parent
                spacing: 5

                Repeater{
                    id: rowRepeater

                    model: content.rowsAmount
                    //model: 3

                    RowLayout {
                        id: rowOfWords
                        Layout.fillWidth: true
                        required property int index
                        spacing: 5

                        Spacer{}

                        Repeater{
                            id: wordRepeater

                            model: ((rowOfWords.index+1) * content.wordsPerRow <= content.displayedWordsSize) ? (content.wordsPerRow) : (content.displayedWordsSize - rowOfWords.index * content.wordsPerRow)


                            WordRectangle{
                                //Layout.fillWidth: true
                                required property int index

                                property string word: application.displayedWords[rowOfWords.index * content.wordsPerRow + index][0] + " " + parent.index
                                property string definition: application.displayedWords[rowOfWords.index * content.wordsPerRow + index][1]
                                property string partOfSpeech: application.displayedWords[rowOfWords.index * content.wordsPerRow + index][2]
                                property string difficulty: application.displayedWords[rowOfWords.index * content.wordsPerRow + index][3]
                                property string url: application.displayedWords[rowOfWords.index * content.wordsPerRow + index][4]
                                property string frequencyOfUse: application.displayedWords[rowOfWords.index * content.wordsPerRow + index][5]
                            }

                        }

                        Spacer{}
                    }


                }

                Spacer{}




            }

        }
    }






    Connections{
        target: application

        function onDisplayedWordsChanged(){
            content.displayedWordsSize = application.getDisplayedWordsSize()
        }
    }

}
