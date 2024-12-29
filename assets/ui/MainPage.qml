pragma ComponentBehavior: Bound

import QtQuick 2.15
import QtQuick.Layouts 2.15
import QtQuick.Controls 2.15

import WordUi 1.0
import TagsUi 1.0
import Cache 1.0

Rectangle{
    id: mainPage
    //anchors.margins: 10
    anchors.centerIn: parent
    width: mainWindow.width// - 2*anchors.margins
    height: mainWindow.height// - 2*anchors.margins

    color: "#ADADAD"
    focus: true


    signal screenChanged(path: string)

    MouseArea{
        anchors.fill: parent

        onClicked: { mainPage.focus = true }
    }

    Rectangle{
        id: menu
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        property bool closed: application.cache.menuClosed

        color: "#697795"
        radius: 50

        width: (closed) ? (70) : (parent.width*0.35)

        MouseArea{
            anchors.fill: parent

            onClicked: { mainPage.focus = true }
        }


        Image {
            id: openCloseButton
            source: (menu.closed) ? "qrc:/arrowRightBlack.png" : "qrc:/arrowLeftBlack.png"
            //source: "qrc:/arrowLeftBlack.png"
            /*transform: Rotation{
                angle: (menu.closed) ? (180) : (0)
            }*/

            //y: (menu.closed) ? (35) : (15)
            anchors.top: parent.top
            anchors.topMargin: 15

            Component.onCompleted: {
                openCloseButton.anchors.horizontalCenter = undefined
                openCloseButton.anchors.right = undefined
                openCloseButton.anchors.rightMargin = 0
                if (menu.closed){
                    openCloseButton.anchors.horizontalCenter = menu.horizontalCenter
                } else{
                    openCloseButton.anchors.right = menu.right
                    openCloseButton.anchors.rightMargin = 20
                }
            }

            Connections{
                target: menu

                function onClosedChanged(){
                    openCloseButton.anchors.horizontalCenter = undefined
                    openCloseButton.anchors.right = undefined
                    openCloseButton.anchors.rightMargin = 0
                    if (menu.closed){
                        openCloseButton.anchors.horizontalCenter = menu.horizontalCenter
                    } else{
                        openCloseButton.anchors.right = menu.right
                        openCloseButton.anchors.rightMargin = 20
                    }
                }
            }



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
            width: parent.width * 0.5
            height: parent.height * 0.08
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top

            color: "#D9D9D9"
            radius: 50

            Text{
                text: "Sorting"
                anchors.centerIn: parent
                font.pointSize: parent.height * 0.4
                font.bold: true
            }
        }

        Rectangle{
            id: descendingOrderLine
            anchors.top: sortingLabel.bottom
            anchors.left: menu.left
            anchors.right: menu.right
            anchors.margins: 7
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

                checked: application.cache.descendingOrderChecked
            }
        }


        Rectangle{
            id: propertyLine
            anchors.top: descendingOrderLine.bottom
            anchors.left: menu.left
            anchors.right: menu.right
            anchors.margins: 7
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
                currentIndex: application.cache.propertyIndex

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
            anchors.margins: 7
            visible: !menu.closed
            width: parent.width * 0.5
            height: parent.height * 0.08
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: propertyLine.bottom

            color: "#D9D9D9"
            radius: 50

            Text{
                text: "Searching"
                anchors.centerIn: parent
                font.pointSize: parent.height * 0.4
                font.bold: true

                verticalAlignment: Text.AlignVCenter
            }
        }


        Rectangle{
            id: caseSensitiveLine
            anchors.top: searchingLabel.bottom
            anchors.left: menu.left
            anchors.right: menu.right
            anchors.margins: 7
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

                checked: application.cache.caseSensitiveChecked
            }
        }



        Rectangle{
            id: property2Line
            anchors.top: caseSensitiveLine.bottom
            anchors.left: menu.left
            anchors.right: menu.right
            anchors.margins: 7
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
                currentIndex: application.cache.property2Index

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
            anchors.margins: 7
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
                currentIndex: application.cache.propertyHasToIndex

            }

        }


        Rectangle{
            id: tagsLabel
            anchors.margins: 10
            visible: !menu.closed
            width: parent.width * 0.5
            height: parent.height * 0.08
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: propertyHasToLine.bottom

            color: "#D9D9D9"
            radius: 50

            Text{
                text: "Tags"
                anchors.centerIn: parent
                font.pointSize: parent.height * 0.4
                font.bold: true

                verticalAlignment: Text.AlignVCenter
            }
        }



        Rectangle{
            id: tagsRect
            visible: !menu.closed

            anchors.top: tagsLabel.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            height: parent.height * 0.2

            color: "transparent"

            anchors.margins: 7


            GridLayout{
                id: tagsLayout

                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                height: parent.height * 0.75

                columnSpacing: 5
                rowSpacing: 3


                columns: width / (80 + columnSpacing)
                rows: height / (30 + rowSpacing)


                property int itemsPerPage: columns * rows


                Repeater{
                    id: chosenTagsRepeater
                    model: (application.getTagsChosenUiSize() < tagsLayout.itemsPerPage) ? (application.getTagsChosenUiSize()) : (tagsLayout.itemsPerPage)

                    Tag{
                        required property int index

                        property string tagName: application.tagsChosenUi[index]
                        property int removeFrom: 1
                        property int addTo: 0
                    }

                    onModelChanged: {
                        chosenTagsRepeater.model = (application.getTagsChosenUiSize() < tagsLayout.itemsPerPage) ? (application.getTagsChosenUiSize()) : (tagsLayout.itemsPerPage)
                    }
                }

                Text{
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    visible: (chosenTagsRepeater.model == 0)

                    text: "No tags chosen"
                    font.bold: true
                    font.pixelSize: width * 0.09

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                onItemsPerPageChanged: {
                    chosenTagsRepeater.model = (application.getTagsChosenUiSize() < tagsLayout.itemsPerPage) ? (application.getTagsChosenUiSize()) : (tagsLayout.itemsPerPage)
                    //wordsRepeater.model = ((content.wordsUiSize - (content.page-1)*wordsGrid.itemsPerPage) < wordsGrid.itemsPerPage) ? (content.wordsUiSize - (content.page-1)*wordsGrid.itemsPerPage) : (wordsGrid.itemsPerPage)
                }

            }

            Rectangle{
                anchors.top: tagsLayout.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                width: parent.width * 0.4

                color: "#848484"

                radius: 45

                Text{
                    anchors.fill: parent
                    anchors.leftMargin: 10
                    anchors.rightMargin: 10
                    text: "Edit tags"
                    color: "#000000"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.bold: true
                    font.pointSize: parent.height * 0.375
                }

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        // open window with tags
                        mainWindow.openEditTagsWindow(0);
                    }
                }
            }
        }

        Rectangle{
            id: resetSettingsButton
            anchors.top: tagsRect.bottom
            anchors.left: menu.left
            anchors.right: menu.right
            anchors.bottom: menu.bottom
            anchors.margins: 10
            anchors.rightMargin: 20
            anchors.leftMargin: 20

            visible: !menu.closed

            color: "#D9D9D9"
            radius: 20

            Text{
                text: "Clear settings"
                anchors.fill: parent
                color: "#000000"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.bold: true
                font.pointSize: parent.height * 0.375
                anchors.leftMargin: 10
                anchors.rightMargin: 10
            }


            MouseArea{
                anchors.fill: parent

                onClicked: {
                    descendingOrderCheckBox.checked = false
                    propertyComboBox.currentIndex = 0
                    caseSensitiveCheckBox.checked = false
                    property2ComboBox.currentIndex = 0
                    propertyHasToComboBox.currentIndex = 0
                    application.resetTagsChosen()
                }
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

        MouseArea{
            anchors.fill: parent

            onClicked: { mainPage.focus = true }
        }


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
                    text: application.cache.userInput
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
                    id: searchButtonMouseArea
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


    Pagination{
        id: pagination
        anchors.bottom: mainPage.bottom
        anchors.horizontalCenter: content.horizontalCenter
        property QtObject contentRect: content
    }



    Rectangle{
        id: content
        anchors.top: toolBar.bottom
        anchors.bottom: pagination.top

        anchors.left: menu.right
        anchors.right: mainPage.right
        anchors.topMargin: 10
        anchors.leftMargin: 10

        color: "transparent"


        property int wordsUiSize: application.getWordsUiSize()
        property int pagesTotal: Math.ceil(wordsUiSize / wordsGrid.itemsPerPage)

        property int page: (application.cache.page < pagesTotal) ? (application.cache.page) : (pagesTotal)

        Component.onCompleted: {
            page = (application.cache.page < pagesTotal) ? (application.cache.page) : (pagesTotal)
        }

        MouseArea{
            anchors.fill: parent

            onClicked: { mainPage.focus = true }
        }

        GridLayout{
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


            Text{
                Layout.fillWidth: true
                Layout.fillHeight: true

                visible: (wordsRepeater.model == 0)

                text: "No words found"
                font.bold: true
                font.pixelSize: width * 0.08

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }


            onItemsPerPageChanged: {
                content.page = content.calculateNewPage()
                previousItemsPerPage = itemsPerPage
                wordsRepeater.model = ((content.wordsUiSize - (content.page-1)*wordsGrid.itemsPerPage) < wordsGrid.itemsPerPage) ? (content.wordsUiSize - (content.page-1)*wordsGrid.itemsPerPage) : (wordsGrid.itemsPerPage)
            }
        }

        onPageChanged: {
            if (page < 1){ page = 1; }
            //mainWindow.userWasOnPage = page

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

    function updateCache(){
        application.cache.page = content.page
        application.cache.userInput = searchInput.text
        application.cache.menuClosed = menu.closed
        application.cache.descendingOrderChecked = descendingOrderCheckBox.checked
        application.cache.propertyIndex = propertyComboBox.currentIndex
        application.cache.caseSensitiveChecked = caseSensitiveCheckBox.checked
        application.cache.property2Index = property2ComboBox.currentIndex
        application.cache.propertyHasToIndex = propertyHasToComboBox.currentIndex
    }

    Keys.onPressed: (event) => {

        if (searchInput.focus && (event.key == Qt.Key_Return)){
            application.searchWords(searchInput.text, property2ComboBox.getProperty(), caseSensitiveCheckBox.checked, (propertyHasToComboBox.currentIndex==1), (propertyHasToComboBox.currentIndex==2));
            mainPage.focus = true
            return;
        }
        if (event.key == Qt.Key_M && (event.modifiers & Qt.ControlModifier)){
            menu.closed = !menu.closed
            return;
        }
        if (!searchInput.focus && event.key == Qt.Key_Slash){
            searchInput.focus = true
            return;
        }
        if (!searchInput.focus && !(event.modifiers & Qt.ShiftModifier) && !(event.modifiers & Qt.ControlModifier) && !(event.modifiers & Qt.AltModifier) && !(event.key == Qt.Key_CapsLock)){
            application.message("Press \"/\" to enter search field", "Just so you know :)", "warning")
        }


    }

    Connections{
        target: application

        function onTagsChosenUiChanged(){
            chosenTagsRepeater.model = null
            chosenTagsRepeater.model = application.getTagsChosenUiSize();
        }
    }

    /*Connections{
        //target: mainPage.activeFocusItem.Keys
        target: mainPage.parent.activeFocusItem.Keys

        function onPressed(event){
            console.log("Key pressed!")
            if (searchInput.focus && event.key == Qt.Key_Enter){
                searchButtonMouseArea.clicked()
                return;
            }
            if (event.key == Qt.Key_M && (event.modifiers & Qt.ShiftModifier)){
                menu.closed = !menu.closed
                return;
            }
            if (!searchInput.focus && event.key == Qt.Key_Slash){
                searchInput.focus = true
                return;
            }
            application.message("Press \"/\" to enter search field", "Just so you know :)", "warning")
        }
    }*/


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







