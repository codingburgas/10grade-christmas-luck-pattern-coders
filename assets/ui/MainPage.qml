pragma ComponentBehavior: Bound

import QtQuick 2.15
import QtQuick.Layouts 2.15
import QtQuick.Controls 2.15

import WordUi 1.0
import TagsUi 1.0

Rectangle{
    id: mainPage
    //anchors.margins: 10
    anchors.centerIn: parent
    width: mainWindow.width// - 2*anchors.margins
    height: mainWindow.height// - 2*anchors.margins

    color: "#ADADAD"


    signal screenChanged(path: string)

    Rectangle{
        id: menu
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        property bool closed: true

        color: "#697795"
        radius: 50

        width: (closed) ? (70) : (parent.width*0.35)

        Image {
            id: openCloseButton
            //source: (menu.closed) ? "qrc:/arrowRightBlack.png" : "qrc:/arrowLeftBlack.png"
            source: "qrc:/arrowLeftBlack.png"
            transform: Rotation{
                angle: (menu.closed) ? (180) : (0)
            }

            y: (menu.closed) ? (35) : (15)
            anchors.right: parent.right
            anchors.rightMargin: (menu.closed) ? (2) : (15)



            MouseArea{
                anchors.fill: parent

                onClicked: {
                    menu.closed = !menu.closed
                }
            }
        }

        Rectangle{
            id: sortingLabel
            anchors.margins: 10
            visible: !menu.closed
            width: parent.width * 0.4
            height: parent.height * 0.1
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top

            color: "#D9D9D9"
            radius: 50

            Text{
                text: "Sorting"
                anchors.centerIn: parent
                font.pointSize: parent.height * 0.2
                font.bold: true
            }
        }

        Rectangle{
            id: descendingOrderLine
            anchors.top: sortingLabel.bottom
            anchors.left: menu.left
            anchors.right: menu.right
            anchors.margins: 10
            height: parent.height * 0.07

            visible: !menu.closed
            color: "transparent"

            Text{
                id: descendingOrderText
                text: "Descending order"
                font.pointSize: parent.height * 0.3
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: parent.width * 0.82

                verticalAlignment: Text.AlignVCenter
            }

            CheckBox{
                id: descendingOrderCheckBox
                anchors.left: descendingOrderText.right
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.margins: 15
            }
        }


        Rectangle{
            id: propertyLine
            anchors.top: descendingOrderLine.bottom
            anchors.left: menu.left
            anchors.right: menu.right
            anchors.margins: 10
            height: parent.height * 0.07

            visible: !menu.closed
            color: "transparent"

            Text{
                id: propertyText
                text: "Property"
                font.pointSize: parent.height * 0.3
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: parent.width * 0.7

                verticalAlignment: Text.AlignVCenter
            }

            ComboBox{
                id: propertyComboBox
                anchors.left: propertyText.right
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom

                anchors.margins: 10

                model: ["Word", "Definition", "Part of speech", "Difficulty", "Frequency of use"]

                function getProperty(){
                    switch (currentIndex){
                    case 0: {
                        return "word"; break;
                    }
                    case 1: {
                        return "definition"; break;
                    }
                    case 2: {
                        return "partOfSpeech"; break;
                    }
                    case 3: {
                        return "difficulty"; break;
                    }
                    case 4: {
                        return "frequencyOfUse"; break;
                    }
                    }
                }
            }

        }


        Rectangle{
            id: searchingLabel
            anchors.margins: 10
            visible: !menu.closed
            width: parent.width * 0.4
            height: parent.height * 0.1
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: propertyLine.bottom

            color: "#D9D9D9"
            radius: 50

            Text{
                text: "Searching"
                anchors.centerIn: parent
                font.pointSize: parent.height * 0.2
                font.bold: true

                verticalAlignment: Text.AlignVCenter
            }
        }


        Rectangle{
            id: caseSensitiveLine
            anchors.top: searchingLabel.bottom
            anchors.left: menu.left
            anchors.right: menu.right
            anchors.margins: 10
            height: parent.height * 0.07

            visible: !menu.closed
            color: "transparent"

            Text{
                id: caseSensitiveText
                text: "Case sensitive"
                font.pointSize: parent.height * 0.3
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: parent.width * 0.82

                verticalAlignment: Text.AlignVCenter
            }

            CheckBox{
                id: caseSensitiveCheckBox
                anchors.left: caseSensitiveText.right
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.margins: 15
            }
        }



        Rectangle{
            id: property2Line
            anchors.top: caseSensitiveLine.bottom
            anchors.left: menu.left
            anchors.right: menu.right
            anchors.margins: 10
            height: parent.height * 0.07

            visible: !menu.closed
            color: "transparent"

            Text{
                id: property2Text
                text: "Property"
                font.pointSize: parent.height * 0.3
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: parent.width * 0.7

                verticalAlignment: Text.AlignVCenter
            }

            ComboBox{
                id: property2ComboBox
                anchors.left: property2Text.right
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom

                anchors.margins: 10

                model: ["Word", "Definition", "Part of speech", "Difficulty"]

                function getProperty(){
                    switch (currentIndex){
                    case 0: {
                        return "word"; break;
                    }
                    case 1: {
                        return "definition"; break;
                    }
                    case 2: {
                        return "partOfSpeech"; break;
                    }
                    case 3: {
                        return "difficulty"; break;
                    }
                    }
                }
            }

        }


        Rectangle{
            id: propertyHasToLine
            anchors.top: property2Line.bottom
            anchors.left: menu.left
            anchors.right: menu.right
            anchors.margins: 10
            height: parent.height * 0.07

            color: "transparent"

            visible: !menu.closed

            Text{
                id: propertyHasToText
                text: "Property has to"
                font.pointSize: parent.height * 0.3
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: parent.width * 0.7
                verticalAlignment: Text.AlignVCenter
            }

            ComboBox{
                id: propertyHasToComboBox
                anchors.left: propertyHasToText.right
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom

                anchors.margins: 10

                model: ["Contain", "Start with", "End with"]

            }

        }


    }

    Rectangle{
        id: toolBar
        height: parent.height * 0.1
        anchors.top: parent.top
        anchors.left: menu.right
        anchors.right: parent.right

        color: "#D9D9D9"
        radius: 50


        RowLayout{
            anchors.fill: parent
            spacing: 5

            Rectangle{
                Layout.preferredWidth: parent.width * 0.6
                Layout.fillHeight: true
                Layout.margins: 5
                Layout.alignment: Qt.AlignRight
                radius: 45
                color: "#848484"
                clip: true

                TextField{
                    id: searchInput
                    color: "#FFFFFF"
                    background: Rectangle{ color: "transparent" }
                    anchors.fill: parent
                    font.pointSize: 18
                    text: ""
                    placeholderText: "Leave blank to get all words"
                    placeholderTextColor: "#FFFFFF"
                    clip: true
                    leftPadding: 15
                    rightPadding: 15
                    verticalAlignment: Text.AlignVCenter
                }
            }



            Rectangle{
                id: searchButton
                Layout.fillHeight: true
                Layout.margins: 5
                Layout.preferredWidth: parent.height - 10
                Layout.alignment: Qt.AlignRight

                radius: 45

                clip: true

                color: "#848484"

                Image{
                    source: "qrc:/magnifyingGlass.png"
                    anchors.fill: parent
                    clip: true
                    anchors.margins: 14
                    //color: "transparent"
                }

                MouseArea{
                    anchors.fill: parent

                    onClicked: {
                        application.searchWords(searchInput.text, property2ComboBox.getProperty(), caseSensitiveCheckBox.checked, (propertyHasToComboBox.currentIndex==1), (propertyHasToComboBox.currentIndex==2));
                    }
                }
            }


            Rectangle{
                id: sortButton
                Layout.fillHeight: true
                Layout.preferredWidth: parent.height - 10
                Layout.alignment: Qt.AlignRight

                Layout.margins: 5
                radius: 45

                clip: true

                color: "#848484"

                Image{
                    source: "qrc:/sortingIcon.png"
                    anchors.fill: parent
                    anchors.margins: 14
                    clip: true
                    //color: "transparent"
                }

                MouseArea{
                    anchors.fill: parent

                    onClicked: {
                        application.sortWords(propertyComboBox.getProperty(), !descendingOrderCheckBox.checked);
                    }
                }
            }

        }
    }






    Rectangle{
        id: content
        anchors.top: toolBar.bottom
        anchors.bottom: mainPage.bottom
        anchors.left: menu.right
        anchors.right: mainPage.right
        anchors.topMargin: 10
        anchors.leftMargin: 10

        color: "transparent"


        property int wordsUiSize: application.getWordsUiSize()
        property int pagesTotal: Math.ceil(wordsUiSize / wordsGrid.itemsPerPage)

        property int page: (mainWindow.userWasOnPage < pagesTotal) ? (mainWindow.userWasOnPage) : (pagesTotal)

        Component.onCompleted: {
            page = page + 1 - 1;
            pageChanged()
        }

        Grid{
            id: wordsGrid

            anchors.fill: parent
            columnSpacing: mainPage.width * 0.01
            rowSpacing: mainPage.height * 0.01


            columns: width / (300 + columnSpacing)
            rows: height / (200 + rowSpacing)


            property int itemsPerPage: columns * rows
            property int previousItemsPerPage: itemsPerPage


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

            onItemsPerPageChanged: {
                content.page = content.calculateNewPage()
                previousItemsPerPage = itemsPerPage
                wordsRepeater.model = ((content.wordsUiSize - (content.page-1)*wordsGrid.itemsPerPage) < wordsGrid.itemsPerPage) ? (content.wordsUiSize - (content.page-1)*wordsGrid.itemsPerPage) : (wordsGrid.itemsPerPage)
            }
        }

        onPageChanged: {
            if (page < 1){ page = 1; }
            mainWindow.userWasOnPage = page

            wordsRepeater.model = null
            wordsRepeater.model = ((content.wordsUiSize - (content.page-1)*wordsGrid.itemsPerPage) < wordsGrid.itemsPerPage) ? (content.wordsUiSize - (content.page-1)*wordsGrid.itemsPerPage) : (wordsGrid.itemsPerPage)


        }

        function calculateNewPage(){
            let firstItemOnOldPageIndex = (page - 1) * wordsGrid.previousItemsPerPage + 1
            let newPage = Math.ceil(firstItemOnOldPageIndex / wordsGrid.itemsPerPage)

            if (newPage < 1){ newPage = 1; }

            return newPage;
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







