pragma ComponentBehavior: Bound

import QtQuick 2.15
import QtQuick.Layouts

Rectangle {
    id: word
    width: 300
    height: 150


    color: "#00dfff"


    ColumnLayout{
        /*Repeater{
            model: 6
            Text{

                required property int index
                color: "#fffb00"
                text: word.data[index]
            }
        }*/
        TextEdit{
            color: "#fffb00"
            //text: word.word
            text: word.wordUi.word

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
            color: "#fffb00"
            //text: word.definition
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
        TextEdit{
            color: "#fffb00"
            //text: word.partOfSpeech
            text: word.wordUi.partOfSpeech

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
            color: "#fffb00"
            //text: word.difficulty
            text: word.wordUi.difficulty

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
            color: "#fffb00"
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
        }
        TextEdit{
            color: "#fffb00"
            //text: word.frequencyOfUse
            text: word.wordUi.frequencyOfUse

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
        Repeater{
            id: tagsRepeater
            model: word.wordUi.getTagsSize()

            TextEdit{
                required property int index
                color: "#fffb00"
                //text: word.frequencyOfUse
                text: word.wordUi.tags[index]

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



    Connections{
        target: word.wordUi

        function onTagsChanged(){
            tagsRepeater.model = word.wordUi.getTagsSize();
        }
    }



}
