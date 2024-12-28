import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle{
    id: paginator
    width: 300
    height: 50
    color: "transparent"
    visible: contentRect.pagesTotal != 1

    border.width: 2
    border.color: "#848484"
    radius: 50


    Rectangle{
        id: backButton
        width: 50
        height: 50
        anchors.left: paginator.left
        visible: (paginator.contentRect.page != 1)

        color: "transparent"

        Image{
            anchors.fill: parent
            anchors.margins: 10
            source: "qrc:/arrowLeftBlack.png"
        }

        MouseArea{
            anchors.fill: parent

            onClicked: {
                paginator.contentRect.page -= 1
            }
        }
    }

    Rectangle{
        id: pageNumber
        width: 200
        height: 50
        color: "transparent"
        anchors.horizontalCenter: paginator.horizontalCenter

        TextField{
            readOnly: true
            anchors.fill: parent
            text: paginator.contentRect.page + " / " + paginator.contentRect.pagesTotal
            font.pointSize: 18

            background: Rectangle{ color: "transparent" }

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

    Rectangle{
        id: nextButton
        width: 50
        height: 50
        anchors.right: paginator.right
        visible: paginator.contentRect.pagesTotal != paginator.contentRect.page

        color: "transparent"


        Image{
            anchors.fill: parent
            anchors.margins: 10
            source: "qrc:/arrowRightBlack.png"
        }


        MouseArea{
            anchors.fill: parent

            onClicked: {
                paginator.contentRect.page += 1
            }
        }
    }



}
