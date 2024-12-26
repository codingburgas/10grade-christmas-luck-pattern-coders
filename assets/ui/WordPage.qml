pragma ComponentBehavior: Bound

import QtQuick 2.15
import WordUi 1.0

Rectangle{
    id: wordPage
    //anchors.margins: 10
    anchors.centerIn: parent
    //width: mainWindow.width - 2*anchors.margins
    //height: mainWindow.height - 2*anchors.margins
    width: mainWindow.width
    height: mainWindow.height
    color: "#ADADADB2"


    signal screenChanged(path: string)

    property WordUi word: application.wordsUi[application.indexOfClickedWord]

    //property int tagsSize: application.getTagsUiSize()


    Rectangle{
        id: title
        width: parent.width * 0.42
        height: parent.height * 0.11
        anchors.top: wordPage.top
        anchors.horizontalCenter: parent.horizontalCenter
        radius: 45
        color: "#D9D9D9"

        Text{
            id: word
            anchors.fill: parent
            text: wordPage.word.word
            color: "#000000"
            font.family: "Inter"
            font.weight: 700
            font.pixelSize: wordPage.height * 0.046
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
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
            text: "Definition:"
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
            color: "#848484"
            radius: 35

            Text{
                id: definitionText

                text: wordPage.word.definition + "\n\nLearn more at " + wordPage.word.url
                anchors.fill: parent
                anchors.margins: wordPage.height * 0.016

                color: "#000000"
                font.family: "Inter"
                font.weight: 400
                font.pixelSize: wordPage.height * 0.027
                verticalAlignment: Text.AlignTop
                wrapMode: Text.WordWrap

            }
        }
    }


    Rectangle{
        id: partOfSpeech
        anchors.left: definition.right
        anchors.top: title.bottom
        width: parent.width * 0.22
        height: parent.width * 0.13


        anchors.margins: wordPage.height * 0.016
        color: "#D9D9D9"
        radius: 35

        Text{
            id: partOfSpeechLabel
            text: "Part of speech:"
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
            color: "#848484"
            radius: 27

            Text{
                id: partOfSpeechText

                text: wordPage.word.partOfSpeech
                anchors.fill: parent
                anchors.leftMargin: wordPage.height * 0.0083

                color: "#000000"
                font.family: "Inter"
                font.weight: 400
                font.pixelSize: wordPage.height * 0.027
                verticalAlignment: Text.AlignVCenter

            }
        }
    }



    Rectangle{
        id: frequencyOfUse
        anchors.left: partOfSpeech.right
        anchors.top: title.bottom
        anchors.right: wordPage.right
        height: parent.width * 0.13


        anchors.margins: wordPage.height * 0.016
        color: "#D9D9D9"
        radius: 35

        Text{
            id: frequencyOfUseLabel
            text: "Frequency of use:"
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
            color: "#848484"
            radius: 27

            Text{
                id: frequencyOfUseText

                text: wordPage.word.frequencyOfUse
                anchors.fill: parent
                anchors.leftMargin: wordPage.height * 0.0083

                color: "#000000"
                font.family: "Inter"
                font.weight: 400
                font.pixelSize: wordPage.height * 0.027
                verticalAlignment: Text.AlignVCenter

            }
        }
    }


    Rectangle{
        id: difficulty
        anchors.left: definition.right
        anchors.top: partOfSpeech.bottom

        width: parent.width * 0.22
        height: parent.width * 0.13



        anchors.margins: wordPage.height * 0.016
        color: "#D9D9D9"
        radius: 35

        Text{
            id: difficultyLabel
            text: "Difficulty:"
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
            color: "#848484"
            radius: 27

            Text{
                id: difficultyText

                text: wordPage.word.difficulty
                anchors.fill: parent
                anchors.leftMargin: wordPage.height * 0.0083

                color: "#000000"
                font.family: "Inter"
                font.weight: 400
                font.pixelSize: wordPage.height * 0.027
                verticalAlignment: Text.AlignVCenter

            }
        }
    }


    Rectangle{
        id: syllablesCount
        anchors.left: difficulty.right
        anchors.top: frequencyOfUse.bottom
        anchors.right: wordPage.right
        height: parent.width * 0.13


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
            color: "#848484"
            radius: 27

            Text{
                id: syllablesCountText

                text: application.countSyllablesOfWord(application.indexOfWordClicked)
                anchors.fill: parent
                anchors.leftMargin: wordPage.height * 0.0083

                color: "#000000"
                font.family: "Inter"
                font.weight: 400
                font.pixelSize: wordPage.height * 0.027
                verticalAlignment: Text.AlignVCenter

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
            color: "#848484"
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
            color: "#848484"
            radius: 27


            Grid{
                spacing: wordPage.height * 0.0083
                anchors.fill: parent
                anchors.margins: wordPage.height * 0.013
                Repeater{
                    id: wordTagsRepeater
                    model: (wordPage.word.getTagsSize() < 6) ? (wordPage.word.getTagsSize()) : (6)

                    Tag{
                        required property int index

                        property int location: 1
                        property bool chosen: true
                    }
                }
            }

        }


    }


    /*Repeater{
        id: wordTagsRepeater
        //anchors.top: title.bottom
        model: wordPage.word.getTagsSize()


        Tag{
            required property int index
            property int location: 1
            property bool chosen: true
            y: 100 + index*100
        }
    }*/

    /*Repeater{
        id: difficultyTagsRepeater
        //anchors.top: title.bottom
        model: application.tagsUi.getDifficultyTagsSize()

        Text{
            required property int index
            x: 100 + index*100
            y: 50
            text: application.tagsUi.difficultyTags[index]
        }
    }

    Repeater{
        id: partOfSpeechTagsRepeater
        //anchors.top: title.bottom
        model: application.tagsUi.getPartOfSpeechTagsSize()

        Text{
            required property int index
            x: 100 + index*100
            y: 100
            text: application.tagsUi.partOfSpeechTags[index]
        }
    }

    Repeater{
        id: customTagsRepeater
        //anchors.top: title.bottom
        model: application.tagsUi.getCustomTagsSize()

        Text{
            required property int index
            x: 100 + index*100
            y: 150
            text: application.tagsUi.customTags[index]
        }
    }*/




    /*MouseArea{
        anchors.fill: parent

        onClicked: {
            // send message
            //application.message(word.text, "description of the message", "type");
            // delete tag of word
            //application.deleteWordTag(application.indexOfClickedWord, 2);
            //add tag to word
            application.addWordTag(application.indexOfClickedWord, 3);
        }
    }*/




    /*
    Connections{
        target: application

        function onTagsUiChanged(){
            wordPage.tagsSize = application.getDisplayedTagsSize();
        }
    }
    */

    Connections{
        target: wordPage.word

        function onTagsChanged(){
            //wordPage.tagsSize = application.getDisplayedTagsSize();
            wordTagsRepeater.model = wordPage.word.getTagsSize()
        }
    }




}
