pragma ComponentBehavior: Bound

import QtQuick 2.15
import QtQuick.Layouts 2.15
import QtQuick.Controls 2.15

import WordUi 1.0
import TagsUi 1.0

Rectangle{
    id: mainPage
    anchors.margins: 10
    anchors.centerIn: parent
    width: mainWindow.width - 2*anchors.margins
    height: mainWindow.height - 2*anchors.margins


    signal screenChanged(path: string)

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
                        application.searchWords(searchInput.text, propertyName, true, startWithCheckBox.checked);
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

            CheckBox{
                id: startWithCheckBox
                text: "Start with"
            }
        }
    }






    Rectangle{
        id: content
        anchors.top: toolBar.bottom
        width: parent.width
        anchors.bottom: mainPage.bottom
        anchors.topMargin: 10
        //Layout.fillHeight: true
        //width: mainWindow.width - 2*anchors.margins
        //height: mainWindow.height - 2*anchors.margins

        //anchors.centerIn: parent

        property int wordRectWidth: 305
        property int wordRectHeight: 155


        property int wordsUiSize: application.getWordsUiSize()

        property int rowsPerPage: content.height / wordRectHeight
        property int previousRowsPerPage: rowsPerPage
        // for calculating page number when resizing the window

        property int wordsPerRow: content.width / content.wordRectWidth
        property int previousWordsPerRow: wordsPerRow

        property int rowsAmount: (wordsUiSize % wordsPerRow == 0) ? (wordsUiSize / wordsPerRow) : ((wordsUiSize / wordsPerRow) + 1)


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

                    //Spacer{}

                    Repeater{
                        id: wordRepeater

                        model: (((content.page-1) * content.rowsPerPage * content.wordsPerRow + (rowOfWords.index+1) * content.wordsPerRow) <= content.wordsUiSize) ? (content.wordsPerRow) : (content.wordsUiSize - ((content.page-1) * content.rowsPerPage * content.wordsPerRow + rowOfWords.index * content.wordsPerRow))


                        WordRectangle{
                            //Layout.fillWidth: true
                            required property int index
                            property int indexInWordsUi: (content.page-1) * content.rowsPerPage * content.wordsPerRow + rowOfWords.index * content.wordsPerRow + index
                            property QtObject page: mainPage


                            property WordUi wordUi: application.wordsUi[indexInWordsUi]
                        }

                    }

                    Spacer{}
                }


            }

            Spacer{}




        }


        onWordsUiSizeChanged: {
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

    Connections{
        target: application

        function onWordsUiChanged(){
            content.wordsUiSize = application.getWordsUiSize()
            application.message(content.wordsUiSize + " words found", "There are " + content.wordsUiSize + " words corresponding to your request", "success")
        }
    }

    /*ColumnLayout{
        id: chosenTags
        width: 300

        Repeater{
            id: chosenTagsRepeater
            model: application.getTagsChosenUiSize()

            Tag{
                property bool chosen: true
                required property int index
            }
        }
    }


    ColumnLayout{
        id: tags
        anchors.left: chosenTags.right
        width: 300

        Repeater{
            id: tagsRepeater
            model: application.tagsUi.getDifficultyTagsSize() + application.tagsUi.getPartOfSpeechTagsSize() + application.tagsUi.getCustomTagsSize()

            Tag{
                property bool chosen: false
                required property int index

            }

        }
    }


    Connections{
        target: application

        function onTagsChosenUiChanged(){
            chosenTagsRepeater.model = application.getTagsChosenUiSize()
            application.message("Title" ,"Detailed description", "error")

        }

        function onTagsUiChanged(){
            tagsRepeater.model = application.tagsUi.getDifficultyTagsSize() + application.tagsUi.getPartOfSpeechTagsSize() + application.tagsUi.getCustomTagsSize()
        }
    }*/
}







