import QtQuick
import QtQuick.Controls

Rectangle {
    id: _root
    anchors.fill: parent
    color: "#ff0000"

    // 作成したModelクラス
    ScreenA {
        id: _model

    }

    // 画面作成後に呼び出される処理
    Component.onCompleted: {

        // Modelクラスから取得した文字列を画面へ反映する
        _label.text = _model.getText();
    }

    Label {
        id: _label

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        font.pixelSize: 32
        color: "#000000"

        text: "画面A"
    }
}

