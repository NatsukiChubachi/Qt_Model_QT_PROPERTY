#include "ScreenA.h"

/**
 * @brief コンストラクタ
 * @param parent
 */
ScreenA::ScreenA(QObject *parent)
    : QObject{parent}
{
    // 処理なし
}


/**
 * @brief Modelクラスから文字列情報を取得する
 * @return 適当な文字列
 */
QString ScreenA::getText()
{
    return QString( "関数getText()\nが呼び出されました。" );
}
