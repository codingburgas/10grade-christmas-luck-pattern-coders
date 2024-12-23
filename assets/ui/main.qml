pragma ComponentBehavior: Bound

import QtQuick 2.15
import QtQuick.Layouts 2.15
import QtQuick.Controls 2.15

Window {
    id: mainWindow
    visible: true
    width: 800
    height: 600
    title: "LEXIFY"


    Rectangle{
        id: mainPart
        anchors.margins: 10
        anchors.centerIn: parent
        width: mainWindow.width - 2*anchors.margins
        height: mainWindow.height - 2*anchors.margins

        Rectangle{
            id: toolBar
            height: 50
            width: parent.width
            Row{
                anchors.fill: parent
                spacing: 5

                Rectangle{
                    width: 400
                    height: 50
                    border.width: 3

                    TextField{
                        id: searchInput
                        anchors.fill: parent
                        font.pointSize: 18
                        text: ""
                        placeholderText: "Leave blank to get all words"

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
                Rectangle{
                    id: sortButton
                    width: 50
                    height: 50
                    border.width: 3

                    MouseArea{
                        anchors.fill: parent

                        onClicked: {
                            var propertyName = "word";
                            application.sortWords(propertyName, false);
                        }
                    }
                }
            }
        }






        Rectangle{
            id: content
            anchors.top: toolBar.bottom
            width: parent.width
            anchors.bottom: mainPart.bottom
            anchors.topMargin: 10
            //Layout.fillHeight: true
            //width: mainWindow.width - 2*anchors.margins
            //height: mainWindow.height - 2*anchors.margins

            //anchors.centerIn: parent

            property int wordRectWidth: 305
            property int wordRectHeight: 155


            property int displayedWordsSize: application.getDisplayedWordsSize()

            property int rowsPerPage: content.height / wordRectHeight
            property int previousRowsPerPage: rowsPerPage
            // for calculating page number when resizing the window

            property int wordsPerRow: content.width / content.wordRectWidth
            property int previousWordsPerRow: wordsPerRow

            property int rowsAmount: (displayedWordsSize % wordsPerRow == 0) ? (displayedWordsSize / wordsPerRow) : ((displayedWordsSize / wordsPerRow) + 1)


            property int page: 1
            property int pagesTotal: (rowsAmount % rowsPerPage == 0) ? (rowsAmount / rowsPerPage) : ((rowsAmount / rowsPerPage) + 1)


            ColumnLayout{
                id: columnLayout
                anchors.fill: parent
                spacing: 5

                Repeater{
                    id: rowRepeater

                    model: (content.page * content.rowsPerPage <= content.rowsAmount) ? (content.rowsPerPage) : (content.rowsAmount - (content.page-1) * content.rowsPerPage)
                    //model: 3

                    RowLayout {
                        id: rowOfWords
                        Layout.fillWidth: true
                        required property int index
                        spacing: 5

                        Spacer{}

                        Repeater{
                            id: wordRepeater

                            model: (((content.page-1) * content.rowsPerPage * content.wordsPerRow + (rowOfWords.index+1) * content.wordsPerRow) <= content.displayedWordsSize) ? (content.wordsPerRow) : (content.displayedWordsSize - ((content.page-1) * content.rowsPerPage * content.wordsPerRow + rowOfWords.index * content.wordsPerRow))


                            WordRectangle{
                                //Layout.fillWidth: true
                                required property int index

                                property string word: application.displayedWords[(content.page-1) * content.rowsPerPage * content.wordsPerRow + rowOfWords.index * content.wordsPerRow + index][0] + " " + parent.index
                                property string definition: application.displayedWords[(content.page-1) * content.rowsPerPage * content.wordsPerRow + rowOfWords.index * content.wordsPerRow + index][1]
                                property string partOfSpeech: application.displayedWords[(content.page-1) * content.rowsPerPage * content.wordsPerRow + rowOfWords.index * content.wordsPerRow + index][2]
                                property string difficulty: application.displayedWords[(content.page-1) * content.rowsPerPage * content.wordsPerRow + rowOfWords.index * content.wordsPerRow + index][3]
                                property string url: application.displayedWords[(content.page-1) * content.rowsPerPage * content.wordsPerRow + rowOfWords.index * content.wordsPerRow + index][4]
                                property string frequencyOfUse: application.displayedWords[(content.page-1) * content.rowsPerPage * content.wordsPerRow + rowOfWords.index * content.wordsPerRow + index][5]
                            }

                        }

                        Spacer{}
                    }


                }

                Spacer{}




            }


            onDisplayedWordsSizeChanged: {
                page = 1;
            }

            function calculateNewPage(){
                var firstElementOnOldPageIndex = (page-1) * previousRowsPerPage * previousWordsPerRow;

                var newPageNumber = firstElementOnOldPageIndex / rowsPerPage / wordsPerRow;


                return Math.ceil(newPageNumber);
            }

            onRowsPerPageChanged: {
                var newPageNumber = calculateNewPage();
                previousRowsPerPage = rowsPerPage
                if (newPageNumber < 1){
                    page = 1;
                }else{
                    page = newPageNumber;
                }
            }

            onWordsPerRowChanged: {
                var newPageNumber = calculateNewPage();
                previousWordsPerRow = wordsPerRow
                if (newPageNumber < 1){
                    page = 1;
                }else{
                    page = newPageNumber;
                }
            }

        }

        Pagination{
            anchors.bottom: content.bottom
            anchors.horizontalCenter: content.horizontalCenter
            property QtObject contentRect: content
        }
    }






    Connections{
        target: application

        function onDisplayedWordsChanged(){
            content.displayedWordsSize = application.getDisplayedWordsSize()
        }
    }

}
