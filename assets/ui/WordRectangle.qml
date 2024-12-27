pragma ComponentBehavior: Bound

import QtQuick 2.15
import QtQuick.Layouts

Rectangle {
    id: word
    //property Rectangle page: Rectangle{ width: 800; height: 600 }
    width: page.width * 0.28
    height: page.height * 0.28


    color: "#D9D9D9"
    radius: 45


    /*ColumnLayout{
        anchors.fill: parent
        anchors.margins: word.page.height * 0.01*/

    TextEdit{
        id: wordText

        anchors.top: word.top
        anchors.topMargin: word.page.height * 0.01
        anchors.left: word.left
        anchors.leftMargin: word.page.height * 0.01
        anchors.right: word.right
        anchors.rightMargin: word.page.height * 0.01
        height: word.page.height * 0.04
        /*Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.verticalStretchFactor: 25
        Layout.alignment: Qt.AlignTop*/


        horizontalAlignment: Text.AlignHCenter
        color: "#000000"
        text: word.wordUi.word
        font.bold: true
        font.italic: true
        font.pixelSize: word.page.height * 0.027

        readOnly: true
        selectByMouse: true
        selectedTextColor: "#2F2F2F"
        selectionColor: "#E0E0E0"

        Component.onCompleted: {
            this.text = elidedText()
        }

        function elidedText(){
            let position = 0
            let elide = true;

            while(true){
                let rect = this.positionToRectangle(position)
                let text = this.text.substring(position, 1)
                if (rect.x > this.width || rect.y > this.height){
                    break;
                }

                if (position >= this.text.length){
                    elide = false;
                    break;
                }

                position++;
            }

            if (elide){
                return this.text.substring(0, position-3) + "..."
            } else{
                return this.text
            }


        }
    }

    TextEdit{
        id: definitionText

        anchors.top: wordText.bottom
        anchors.topMargin: word.page.height * 0.01
        anchors.left: word.left
        anchors.leftMargin: word.page.height * 0.01
        anchors.right: word.right
        anchors.rightMargin: word.page.height * 0.01
        height: word.page.height * 0.03
        //Layout.fillWidth: true
        /*Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.verticalStretchFactor: 15
        Layout.alignment: Qt.AlignTop*/

        color: "#000000"
        text: word.wordUi.definition

        readOnly: true
        selectByMouse: true
        selectedTextColor: "#2F2F2F"
        selectionColor: "#E0E0E0"

        Component.onCompleted: {
            this.text = elidedText()
        }

        function elidedText(){
            let position = 0
            let elide = true;

            while(true){
                let rect = this.positionToRectangle(position)
                let text = this.text.substring(position, 1)
                if (rect.x > this.width || rect.y > this.height){
                    break;
                }

                if (position >= this.text.length){
                    elide = false;
                    break;
                }

                position++;
            }

            if (elide){
                return this.text.substring(0, position-3) + "..."
            } else{
                return this.text
            }


        }
    }


    /*TextEdit{
        color: "#000000"
        //text: word.url
        text: word.wordUi.url

        readOnly: true
        selectByMouse: true
        selectedTextColor: "#2F2F2F"
        selectionColor: "#E0E0E0"

        Component.onCompleted: {
            this.text = elidedText()
        }

        function elidedText(){
            let position = 0
            let elide = true;

            while(true){
                let rect = this.positionToRectangle(position)
                let text = this.text.substring(position, 1)
                if (rect.x > this.width || rect.y > this.height){
                    break;
                }

                if (position >= this.text.length){
                    elide = false;
                    break;
                }

                position++;
            }

            if (elide){
                return this.text.substring(0, position-3) + "..."
            } else{
                return this.text
            }


        }
    }*/

    TextEdit{
        id: frequencyOfUseText

        anchors.top: definitionText.bottom
        anchors.topMargin: word.page.height * 0.01
        anchors.left: word.left
        anchors.leftMargin: word.page.height * 0.01
        anchors.right: word.right
        anchors.rightMargin: word.page.height * 0.01
        height: word.page.height * 0.03
        /*Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.verticalStretchFactor: 15
        Layout.alignment: Qt.AlignTop*/

        color: "#000000"
        //text: word.frequencyOfUse
        text: "Viewed :" + word.wordUi.frequencyOfUse + " times"

        readOnly: true
        selectByMouse: true
        selectedTextColor: "#2F2F2F"
        selectionColor: "#E0E0E0"

        Component.onCompleted: {
            this.text = elidedText()
        }

        function elidedText(){
            let position = 0
            let elide = true;

            while(true){
                let rect = this.positionToRectangle(position)
                let text = this.text.substring(position, 1)
                if (rect.x > this.width || rect.y > this.height){
                    break;
                }

                if (position >= this.text.length){
                    elide = false;
                    break;
                }

                position++;
            }

            if (elide){
                return this.text.substring(0, position-3) + "..."
            } else{
                return this.text
            }


        }
    }

    Grid{
        id: tagsGrid
        anchors.top: frequencyOfUseText.bottom
        anchors.left: word.left
        anchors.right: word.right
        anchors.bottom: word.bottom
        anchors.margins: word.page.height * 0.01

        rowSpacing: word.page.height * 0.01
        columnSpacing: word.page.height * 0.01

        property rect tagSize: Qt.rect(0, 0, 80, 30)
        columns: parent.width / (tagSize.width + columnSpacing)
        rows: parent.height / (tagSize.width + rowSpacing)
        /*Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.verticalStretchFactor: 45
        Layout.alignment: Qt.AlignBottom*/

        Repeater{
            id: tagsRepeater
            property int tagsSize: word.wordUi.getTagsSize()
            model: (tagsSize < tagsGrid.rows * tagsGrid.columns) ? (tagsSize) : (tagsGrid.rows * tagsGrid.columns)
            //anchors.fill: parent

            Tag{
                required property int index
                property string tagName: word.wordUi.tags[index]
                property int removeFrom: 0
                property int addTo: 0
            }
        }

        onWidthChanged: {
            tagsGrid.columns = word.width / (tagSize.width + tagsGrid.columnSpacing)
            tagsRepeater.model = (tagsRepeater.tagsSize < tagsGrid.rows * tagsGrid.columns) ? (tagsRepeater.tagsSize) : (tagsGrid.rows * tagsGrid.columns)
        }
        onHeightChanged: {
            tagsGrid.rows = word.height / (tagSize.width + tagsGrid.rowSpacing)
            tagsRepeater.model = (tagsRepeater.tagsSize < tagsGrid.rows * tagsGrid.columns) ? (tagsRepeater.tagsSize) : (tagsGrid.rows * tagsGrid.columns)
        }
    }



    MouseArea{
        anchors.fill: parent

        onClicked: {
            //console.log(word.indexInWordsUi)
            application.increaseWordFrequncyOfUse(word.indexInWordsUi);
            application.indexOfClickedWord = word.indexInWordsUi;
            word.page.screenChanged("WordPage.qml");
        }
    }



    /*Connections{
        target: word.wordUi

        function onTagsChanged(){
            let size = word.wordUi.getTagsSize();
            tagsRepeater.model = (size < tagsGrid.rows * tagsGrid.columns) ? (size) : (tagsGrid.rows * tagsGrid.columns)
        }
    }*/



}
