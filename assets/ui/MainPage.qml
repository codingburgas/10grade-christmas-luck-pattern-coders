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


        property int wordsUiSize: application.getWordsUiSize()
        property int page: mainWindow.userWasOnPage
        property int pagesTotal: Math.ceil(wordsUiSize / wordsGrid.itemsPerPage)

        Component.onCompleted: {
            page = page + 1 - 1;
            pageChanged()
        }

        Grid{
            id: wordsGrid

            anchors.fill: parent
            columnSpacing: mainPage.width * 0.01
            rowSpacing: mainPage.height * 0.01


            columns: width / (mainPage.width * 0.28 + columnSpacing)
            rows: height / (mainPage.height * 0.28 + rowSpacing)


            property int itemsPerPage: columns * rows


            Repeater{
                id: wordsRepeater
                model: ((content.wordsUiSize - (content.page-1)*wordsGrid.itemsPerPage) < wordsGrid.itemsPerPage) ? (content.wordsUiSize - (content.page-1)*wordsGrid.itemsPerPage) : (wordsGrid.itemsPerPage)

                WordRectangle{
                    //Layout.fillWidth: true
                    required property int index
                    property int indexInWordsUi: (content.page-1) * wordsGrid.itemsPerPage + index
                    property QtObject page: mainPage


                    property WordUi wordUi: application.wordsUi[indexInWordsUi]


                }
            }
        }

        onPageChanged: {
            if (page < 1){ page = 1; }
            mainWindow.userWasOnPage = page
            wordsRepeater.model = null
            wordsRepeater.model = ((content.wordsUiSize - (content.page-1)*wordsGrid.itemsPerPage) < wordsGrid.itemsPerPage) ? (content.wordsUiSize - (content.page-1)*wordsGrid.itemsPerPage) : (wordsGrid.itemsPerPage)

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
            if (content.page != 1){
                content.page = 1
            } else{
                content.pageChanged()
            }

            //application.message(content.wordsUiSize + " words found", "There are " + content.wordsUiSize + " words corresponding to your request", "success")
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







