pragma ComponentBehavior: Bound

import QtQuick 2.15
import QtQuick.Controls 2.15
import WordUi 1.0

Rectangle{
    id: wordPage
    anchors.centerIn: parent
    width: mainWindow.width
    height: mainWindow.height
    color: "#ADADADB2"


    signal screenChanged(path: string)

    property WordUi word: application.wordsUi[application.indexOfClickedWord]

    Rectangle{
        id: backButton

        anchors.top: wordPage.top
        anchors.left: wordPage.left
        anchors.leftMargin: parent.height * 0.016
        color: "transparent"
        border.width: 10
        border.color: "#8BAD88"

        width: parent.height * 0.11
        height: parent.height * 0.11

        radius: 50

        Image{
            anchors.centerIn: parent
            width: parent.width * 0.7
            height: parent.height * 0.7

            source: "qrc:/arrowLeftGreen.png"
        }

        MouseArea{
            anchors.fill: parent

            onClicked: {
                wordPage.screenChanged("MainPage.qml");
            }
        }
    }



    Rectangle{
        id: title
        width: parent.width * 0.42
        height: parent.height * 0.11
        anchors.top: wordPage.top
        anchors.horizontalCenter: parent.horizontalCenter
        radius: 45
        color: "#D9D9D9"

        TextEdit{
            id: word
            anchors.fill: parent
            text: wordPage.word.word
            color: "#000000"
            font.family: "Inter"
            font.weight: 700
            font.pixelSize: wordPage.height * 0.046
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter

            readOnly: true
            selectByMouse: true
            selectedTextColor: "#ffffff"
            selectionColor: "#5969c9"

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

    }


    Rectangle{
        id: definition
        width: parent.width * 0.49
        anchors.left: wordPage.left
        anchors.top: title.bottom
        anchors.bottom: wordPage.bottom

        anchors.margins: parent.height * 0.016
        color: "#D9D9D9"
        radius: 45

        Text{
            id: definitionLabel
            text: "Definition"
            anchors.margins: wordPage.height * 0.016
            anchors.leftMargin: wordPage.height * 0.025
            anchors.top: definition.top
            anchors.left: definition.left
            anchors.right: definition.right

            height: wordPage.height * 0.06

            color: "#000000"
            font.family: "Inter"
            font.weight: 400
            font.pixelSize: wordPage.height * 0.027
            verticalAlignment: Text.AlignVCenter
        }

        Rectangle{
            id: innerRectangleDefinition

            anchors.left: definition.left
            anchors.top: definitionLabel.bottom
            anchors.bottom: definition.bottom
            anchors.right: definition.right

            anchors.margins: wordPage.height * 0.016
            color: "#FFFFFF"
            radius: 35

            TextEdit{
                id: definitionText

                text: wordPage.word.definition
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                height: parent.height * 0.75
                anchors.margins: wordPage.height * 0.016

                color: "#000000"
                font.family: "Inter"
                font.weight: 400
                font.pixelSize: wordPage.height * 0.027
                verticalAlignment: Text.AlignTop
                wrapMode: Text.WordWrap

                readOnly: true
                selectByMouse: true
                selectedTextColor: "#ffffff"
                selectionColor: "#5969c9"

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
                id: urlText

                text: "Learn more at\n<a href='" + wordPage.word.url + "'>" + wordPage.word.url + "</a>"
                anchors.top: definitionText.bottom
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: wordPage.height * 0.016
                anchors.rightMargin: wordPage.height * 0.016

                color: "#000000"
                font.family: "Inter"
                font.weight: 400
                font.pixelSize: wordPage.height * 0.027
                verticalAlignment: Text.AlignTop
                wrapMode: Text.WordWrap

                readOnly: true
                selectByMouse: true
                selectedTextColor: "#ffffff"
                selectionColor: "#5969c9"

                textFormat: TextEdit.RichText
                onLinkActivated: (link) => {console.log(link); Qt.openUrlExternally(link) }

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
        }
    }


    Rectangle{
        id: partOfSpeech
        anchors.left: definition.right
        anchors.top: title.bottom
        width: parent.width * 0.22
        height: parent.height * 0.17


        anchors.margins: wordPage.height * 0.016
        color: "#D9D9D9"
        radius: 35

        Text{
            id: partOfSpeechLabel
            text: "Part of speech"
            anchors.margins: wordPage.height * 0.01
            anchors.leftMargin: wordPage.height * 0.041
            anchors.top: partOfSpeech.top
            anchors.left: partOfSpeech.left
            anchors.right: partOfSpeech.right

            height: wordPage.height * 0.037

            color: "#000000"
            font.family: "Inter"
            font.weight: 400
            font.pixelSize: wordPage.height * 0.027
            verticalAlignment: Text.AlignVCenter
        }

        Rectangle{
            id: innerRectanglePartOfSpeech

            anchors.left: partOfSpeech.left
            anchors.top: partOfSpeechLabel.bottom
            anchors.bottom: partOfSpeech.bottom
            anchors.right: partOfSpeech.right

            anchors.margins: wordPage.height * 0.013
            color: "#FFFFFF"
            radius: 27

            TextEdit{
                id: partOfSpeechText

                text: wordPage.word.partOfSpeech
                anchors.fill: parent
                anchors.leftMargin: wordPage.height * 0.0083

                color: "#000000"
                font.family: "Inter"
                font.weight: 400
                font.pixelSize: wordPage.height * 0.027
                verticalAlignment: Text.AlignVCenter

                readOnly: true
                selectByMouse: true
                selectedTextColor: "#ffffff"
                selectionColor: "#5969c9"

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
        }
    }



    Rectangle{
        id: frequencyOfUse
        anchors.left: partOfSpeech.right
        anchors.top: title.bottom
        anchors.right: wordPage.right
        height: parent.height * 0.17


        anchors.margins: wordPage.height * 0.016
        color: "#D9D9D9"
        radius: 35

        Text{
            id: frequencyOfUseLabel
            text: "Frequency of use"
            anchors.margins: wordPage.height * 0.01
            anchors.leftMargin: wordPage.height * 0.041
            anchors.top: frequencyOfUse.top
            anchors.left: frequencyOfUse.left
            anchors.right: frequencyOfUse.right

            height: wordPage.height * 0.037

            color: "#000000"
            font.family: "Inter"
            font.weight: 400
            font.pixelSize: wordPage.height * 0.027
            verticalAlignment: Text.AlignVCenter
        }

        Rectangle{
            id: innerRectangleFrequencyOfUse

            anchors.left: frequencyOfUse.left
            anchors.top: frequencyOfUseLabel.bottom
            anchors.bottom: frequencyOfUse.bottom
            anchors.right: frequencyOfUse.right

            anchors.margins: wordPage.height * 0.013
            color: "#FFFFFF"
            radius: 27

            TextEdit{
                id: frequencyOfUseText

                text: wordPage.word.frequencyOfUse
                anchors.fill: parent
                anchors.leftMargin: wordPage.height * 0.0083

                color: "#000000"
                font.family: "Inter"
                font.weight: 400
                font.pixelSize: wordPage.height * 0.027
                verticalAlignment: Text.AlignVCenter


                readOnly: true
                selectByMouse: true
                selectedTextColor: "#ffffff"
                selectionColor: "#5969c9"

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
        }
    }


    Rectangle{
        id: difficulty
        anchors.left: definition.right
        anchors.top: partOfSpeech.bottom

        width: parent.width * 0.22
        height: parent.height * 0.17



        anchors.margins: wordPage.height * 0.016
        color: "#D9D9D9"
        radius: 35

        Text{
            id: difficultyLabel
            text: "Difficulty"
            anchors.margins: wordPage.height * 0.01
            anchors.leftMargin: wordPage.height * 0.041
            anchors.top: difficulty.top
            anchors.left: difficulty.left
            anchors.right: difficulty.right

            height: wordPage.height * 0.037

            color: "#000000"
            font.family: "Inter"
            font.weight: 400
            font.pixelSize: wordPage.height * 0.027
            verticalAlignment: Text.AlignVCenter
        }

        Rectangle{
            id: innerRectangleDifficulty

            anchors.left: difficulty.left
            anchors.top: difficultyLabel.bottom
            anchors.bottom: difficulty.bottom
            anchors.right: difficulty.right

            anchors.margins: wordPage.height * 0.013
            color: "#FFFFFF"
            radius: 27

            TextEdit{
                id: difficultyText

                text: wordPage.word.difficulty
                anchors.fill: parent
                anchors.leftMargin: wordPage.height * 0.0083

                color: "#000000"
                font.family: "Inter"
                font.weight: 400
                font.pixelSize: wordPage.height * 0.027
                verticalAlignment: Text.AlignVCenter


                readOnly: true
                selectByMouse: true
                selectedTextColor: "#ffffff"
                selectionColor: "#5969c9"

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
        }
    }


    Rectangle{
        id: syllablesCount
        anchors.left: difficulty.right
        anchors.top: frequencyOfUse.bottom
        anchors.right: wordPage.right
        height: parent.height * 0.17


        anchors.margins: wordPage.height * 0.016
        color: "#D9D9D9"
        radius: 35

        Text{
            id: syllablesCountLabel
            text: "Syllables count"
            anchors.margins: wordPage.height * 0.01
            anchors.leftMargin: wordPage.height * 0.043
            anchors.top: syllablesCount.top
            anchors.left: syllablesCount.left
            anchors.right: syllablesCount.right

            height: wordPage.height * 0.037

            color: "#000000"
            font.family: "Inter"
            font.weight: 400
            font.pixelSize: wordPage.height * 0.027
            verticalAlignment: Text.AlignVCenter
        }

        Rectangle{
            id: innerRectangleSyllablesCount

            anchors.left: syllablesCount.left
            anchors.top: syllablesCountLabel.bottom
            anchors.bottom: syllablesCount.bottom
            anchors.right: syllablesCount.right

            anchors.margins: wordPage.height * 0.013
            color: "#FFFFFF"
            radius: 27

            TextEdit{
                id: syllablesCountText

                text: application.countSyllablesOfWord(application.indexOfClickedWord)
                anchors.fill: parent
                anchors.leftMargin: wordPage.height * 0.0083

                color: "#000000"
                font.family: "Inter"
                font.weight: 400
                font.pixelSize: wordPage.height * 0.027
                verticalAlignment: Text.AlignVCenter

                readOnly: true
                selectByMouse: true
                selectedTextColor: "#ffffff"
                selectionColor: "#5969c9"

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
        }
    }



    Rectangle{
        id: tags
        anchors.left: definition.right
        anchors.right: wordPage.right
        anchors.top: difficulty.bottom
        anchors.bottom: wordPage.bottom


        anchors.margins: wordPage.height * 0.016
        color: "#D9D9D9"
        radius: 35


        Rectangle{
            id: editTags

            anchors.bottom: tags.bottom
            anchors.horizontalCenter: tags.horizontalCenter
            width: wordPage.width * 0.195
            height: wordPage.height * 0.046

            anchors.margins: wordPage.height * 0.013
            color: "#FFFFFF"
            radius: 27

            Text{
                id: editTagsText

                text: "Edit tags"
                anchors.fill: parent
                anchors.leftMargin: wordPage.height * 0.0083

                color: "#000000"
                font.family: "Inter"
                font.weight: 400
                font.pixelSize: wordPage.height * 0.027
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            MouseArea{
                anchors.fill: parent

                onClicked: {
                    // open window with tags
                    mainWindow.openEditTagsWindow(1);
                }
            }
        }



        Text{
            id: tagsLabel
            text: "Tags:"
            anchors.margins: wordPage.height * 0.01
            anchors.leftMargin: wordPage.height * 0.043
            anchors.top: tags.top
            anchors.left: tags.left
            anchors.right: tags.right

            height: wordPage.height * 0.037

            color: "#000000"
            font.family: "Inter"
            font.weight: 400
            font.pixelSize: wordPage.height * 0.027
            verticalAlignment: Text.AlignVCenter
        }

        Rectangle{
            id: innerRectangleTags

            anchors.left: tags.left
            anchors.top: tagsLabel.bottom
            anchors.bottom: editTags.top
            anchors.right: tags.right
            anchors.margins: wordPage.height * 0.013
            color: "#FFFFFF"
            radius: 27


            Grid{
                id: tagsGrid
                spacing: wordPage.height * 0.0083
                anchors.fill: parent
                anchors.margins: wordPage.height * 0.013

                columns: Math.max(1, Math.floor(width / (80 + spacing)))
                rows: height / (30 + spacing)

                Repeater{
                    id: wordTagsRepeater
                    model: (wordPage.word.getTagsSize() < tagsGrid.columns * tagsGrid.rows) ? (wordPage.word.getTagsSize()) : (tagsGrid.columns * tagsGrid.rows)

                    Tag{
                        required property int index

                        property string tagName: wordPage.word.tags[index]
                        property int removeFrom: 0
                        property int addTo: 0
                        property bool deleteButton: false
                    }

                    onModelChanged: {
                        tagsGrid.forceLayout()
                    }
                }
            }

        }


    }


    Connections{
        target: application

        function onWordTagsChanged(){
            wordTagsRepeater.model = wordPage.word.getTagsSize()
        }
    }




}
