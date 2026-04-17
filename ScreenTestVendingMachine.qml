import QtQuick
import QtQuick.Controls

Rectangle {
    id: _root

    // 背景色
    color: "#FFFFFF"

    // 入金ボタンリスト (text:表示文言, price:入金金額)
    property var coinList: [
        { "text": "1円", "price": 1 },
        { "text": "10円", "price": 10 },
        { "text": "50円", "price": 50 },
        { "text": "100円", "price": 100 }
    ]

    // 商品リスト (text:表示文言, price:値段)
    property var merchandiseList: [
        { "text": "商品A\n100縁", "price": 100 },
        { "text": "商品B\n150縁", "price": 150 },
        { "text": "商品C\n200縁", "price": 200 },
        { "text": "商品D\n500縁", "price": 500 }
    ]

    // 画面作成時に実行されるComponent.onCompleted
    Component.onCompleted: {

        // Modelのinitialize関数を呼び出し現在値を初期化する
        // 初期化した現在値の値をLabelへ反映する
        var value = _model.initialize();
        _lbl_nowValue.text = value;
    }

    // Model配置
    ScreenTestVendingMachine {
        id: _model

        onSigChangedExecState: {
            console.log( "***状態遷移しました***: " + _model.execState );
        }
    }

    // 現在金額表示領域
    // Rectangleで表示した枠内に「現在値」の値を表示する
    Rectangle {
        id: _nowvalue_display

        color: "#FFFFFF"
        border.color: "#000000"
        border.width: 2

        anchors.top: parent.top
        anchors.topMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10

        height: 48

        Label {
            id: _lbl_nowValue

            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.verticalCenter: parent.verticalCenter

            font.pixelSize: 24
            color: "#000000"

            // 「現在値」の値
            text: qsTr( "未初期化" )
        }
    }

    // 取消ボタン
    Button {
        id: _buttonCancel

        anchors.right: _nowvalue_display.right
        anchors.top: _nowvalue_display.bottom
        anchors.topMargin: 10

        width: 200
        height: 50
        palette.buttonText: "#000000"
        text: qsTr( "取り消し" )

        // 入金中のときのみ活性、それ以外は非活性
        enabled: ( _model.execState === 2 ) ? true : false

        // ボタン押下時の動作呼び出し
        onClicked: {

            _lbl_nowValue.text = _model.clickedButtonCancel();
        }
    }

    // 金額ボタン
    Row {
        id: _rowCoin

        anchors.top: _buttonCancel.bottom
        anchors.topMargin: 10
        anchors.left: _nowvalue_display.left

        spacing: 10

        // アイドル状態か入金中状態のみ活性、それ以外は非活性
        enabled: ( _model.execState === 1 || _model.execState === 2 ) ? true : false

        Repeater {
            model: coinList.length

            Button {
                width: 75
                height: 50
                palette.buttonText: "#000000"
                text: coinList[ index ].text

                // ボタン押下時の動作呼び出し
                onClicked: {

                    // console.log( coinList[ index ].price );
                    _lbl_nowValue.text = _model.clickedButtonCoin( coinList[ index ].price );
                }
            }
        }
    }

    // 商品ボタン
    Row {
        id: rowMerchandise

        anchors.top: _rowCoin.bottom
        anchors.topMargin: 10
        anchors.left: _rowCoin.left

        spacing: 10

        Repeater {
            model: merchandiseList.length


            Button {
                width: 150
                height: 250
                palette.buttonText: "#000000"
                text: merchandiseList[ index ].text

                // アイドル状態かつ現在金額で購入可能な場合のみ活性、それ以外は非活性
                enabled: ( _model.execState === 1 && Number( _lbl_nowValue ) >= merchandiseList[ index ].price ) ? true : false

                // ボタン押下時の動作呼び出し
                onClicked: {

                    // console.log( merchandiseList[ index ].price );
                    _lbl_nowValue.text = _model.clickedButtonMerchandise( merchandiseList[ index ].price );
                }
            }
        }
    }
}
