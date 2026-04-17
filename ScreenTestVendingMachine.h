#ifndef __SCREENTESTVENDINGMACHINE_H__
#define __SCREENTESTVENDINGMACHINE_H__

#include <QObject>
#include <QtQml>

class ScreenTestVendingMachine : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    // Q_PROPERTYによるQMLへの変更通知
    Q_PROPERTY( int execState READ getExecState NOTIFY sigChangedExecState );


public:

    /**
     * @brief コンストラクタ
     * @param parent
     */
    explicit ScreenTestVendingMachine(QObject *parent = nullptr);

    /**
     * @brief 初期化関数
     * @return 初期化した現在値(QString)
     * @note 画面のComponent.onCompleted時に１回だけ呼び出される
     */
    Q_INVOKABLE QString initialize( void );

    /**
     * @brief 画面の取り消しボタンが押下されたときに呼び出される関数
     * @return クリアされた現在値を返す
     */
    Q_INVOKABLE QString clickedButtonCancel();

    /**
     * @brief 画面のコインボタンが押下された時に呼び出される関数
     * @param price 押下されたコインボタンのprice
     * @return ボタン押下により更新された現在値(QString)
     * @note ボタンに対応するコインの値に応じて現在値を返す
     */
    Q_INVOKABLE QString clickedButtonCoin( int price );

    /**
     * @brief 画面の商品ボタンが押下された時に呼び出される関数
     * @param price 押下された商品ボタンのprice
     * @return 商品金額に応じてマイナスされた現在値を返す
     */
    Q_INVOKABLE QString clickedButtonMerchandise( int price );


private:
    /**
     * @brief 実行状態のRead関数
     * @return 現在の実行状態の値
     */
    int getExecState();


public:
signals:
    /**
     * @brief 実行状態変数の値が更新された際に通知するシグナル
     */
    void sigChangedExecState();


private:
    /**
     * メンバ変数
     */

    // 状態定義
    enum ExecState{
        None = -1,          // 未初期化状態
        Initialize = 0,     // 初期化状態
        Idle,               // アイドル状態
        Depositing,         // 入金中状態
        Cancel,             // 取消手続状態
        Purchase,           // 購入手続中
    };

    // 実行状態
    ExecState _execState;
    // 現在値
    int _nowValue;

};

#endif // __SCREENTESTVENDINGMACHINE_H__
