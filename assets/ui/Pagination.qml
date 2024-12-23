import QtQuick 2.15
//import QtQuick.Controls 2.15

Rectangle{
    id: paginator
    width: 200
    height: 50
    visible: contentRect.pagesTotal != 1


    Rectangle{
        id: backButton
        width: 50
        height: 50
        border.width: 3
        anchors.left: paginator.left
        visible: (paginator.contentRect.page != 1)

        MouseArea{
            anchors.fill: parent

            onClicked: {
                paginator.contentRect.page -= 1
            }
        }
    }

    Rectangle{
        id: pageNumber
        width: 50
        height: 50
        border.width: 3
        anchors.horizontalCenter: paginator.horizontalCenter

        Text{
            anchors.fill: parent
            text: paginator.contentRect.page
            font.pointSize: 18

        }
    }

    Rectangle{
        id: nextButton
        width: 50
        height: 50
        border.width: 3
        anchors.right: paginator.right
        visible: paginator.contentRect.pagesTotal != paginator.contentRect.page

        MouseArea{
            anchors.fill: parent

            onClicked: {
                paginator.contentRect.page += 1
            }
        }
    }



}
