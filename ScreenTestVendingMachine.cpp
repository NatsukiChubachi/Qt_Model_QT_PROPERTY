#include "ScreenTestVendingMachine.h"

/**
 * @brief コンストラクタ
 * @param parent
 */
ScreenTestVendingMachine::ScreenTestVendingMachine(QObject *parent)
    : QObject{parent}
    , _execState( ExecState::None )
    , _nowValue( 0 )
{
    // 実行状態の更新と通知
    // 初期化状態にセット
    this->_execState = ExecState::Initialize;
    emit this->sigChangedExecState();
}

/**
 * @brief 初期化関数
 * @return 初期化した現在値(QString)
 * @note 画面のComponent.onCompleted時に１回だけ呼び出される
 */
QString ScreenTestVendingMachine::initialize( void )
{
    // 取り消し時の処理を呼び出し画面状態を初期化する
    QString result = this->clickedButtonCancel();

    // 実行状態の更新と通知
    // 初期化処理後にアイドル状態へ遷移
    this->_execState = ExecState::Idle;
    emit this->sigChangedExecState();

    return result;
}

/**
 * @brief 画面の取り消しボタンが押下されたときに呼び出される関数
 * @return クリアされた現在値を返す
 */
QString ScreenTestVendingMachine::clickedButtonCancel()
{
    // 実行状態の更新と通知
    // キャンセル状態へ遷移
    this->_execState = ExecState::Cancel;
    emit this->sigChangedExecState();

    // 現在値をクリアする
    this->_nowValue = 0;

    // QTimerのsingleShotを使用して3秒後に呼ばれる処理を作成する
    QTimer::singleShot( 3000, this, [&]() {
        // 実行状態の更新と通知
        // キャンセル状態からアイドル状態へ遷移
        this->_execState = ExecState::Idle;
        emit this->sigChangedExecState();
    });

    // 更新した現在値をreturnする
    return QString( "%1" ).arg( this->_nowValue );
}

/**
 * @brief 画面のコインボタンが押下された時に呼び出される関数
 * @param price 押下されたコインボタンのprice
 * @return ボタン押下により更新された現在値(QString)
 * @note ボタンに対応するコインの値に応じて現在値を返す
 */
QString ScreenTestVendingMachine::clickedButtonCoin( int price )
{
    // 実行状態の更新と通知
    // アイドル状態から入金状態へ遷移
    if ( this->_nowValue == 0 ) {

        this->_execState = ExecState::Depositing;
        emit this->sigChangedExecState();
    }

    // ボタンに対応した値を現在値に加算する
    this->_nowValue += price;

    // 更新した現在値をreturnする
    return QString( "%1" ).arg( this->_nowValue );
}

/**
 * @brief 画面の商品ボタンが押下された時に呼び出される関数
 * @param price 押下された商品ボタンのprice
 * @return 商品金額に応じてマイナスされた現在値を返す
 */
QString ScreenTestVendingMachine::clickedButtonMerchandise( int price )
{
    // 実行状態の更新と通知
    // 購入手続中状態へ遷移
    this->_execState = ExecState::Purchase;
    emit this->sigChangedExecState();

    // ボタンに対応した値を現在値からマイナスする
    this->_nowValue -= price;

    // QTimerのsingleShotを使用して3秒後に呼ばれる処理を作成する
    QTimer::singleShot( 3000, this, [&]() {
        // 実行状態の更新と通知
        // キャンセル状態からアイドル状態へ遷移
        this->_execState = ExecState::Idle;
        emit this->sigChangedExecState();
    });

    // 更新した現在値をreturnする
    return QString( "%1" ).arg( this->_nowValue );
}

/**
 * @brief 実行状態のRead関数
 * @return 現在の実行状態の値
 */
int ScreenTestVendingMachine::getExecState()
{
    // 現在の状態値を返す
    return (int)( this->_execState );
}
