import QtQuick
import QtQuick.Controls

Window {
    width: 640
    height: 480
    visible: true
    title: "Qt_Model_QT_PROPERTY"

    // 画面QMLを読み込むLoader
    Loader {
        id: _loader
        anchors.fill: parent
    }

    // Window表示時に実行される処理
    Component.onCompleted: {

        // Loaderのsourceプロパティに画面Aのファイルパスを設定する
        _loader.source = "ScreenTestVendingMachine.qml";
    }
}

