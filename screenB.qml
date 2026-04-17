import QtQuick
import QtQuick.Controls

Rectangle {
    id: _root
    anchors.fill: parent
    color: "#0000ff"

    Label {
        id: _label

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        font.pixelSize: 48
        color: "#000000"

        text: "画面B"
    }
}

