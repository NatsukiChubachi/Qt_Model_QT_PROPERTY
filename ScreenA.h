#ifndef SCREENA_H
#define SCREENA_H

#include <QObject>
#include <QtQml>

class ScreenA : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:

    /**
     * @brief コンストラクタ
     * @param parent
     */
    explicit ScreenA(QObject *parent = nullptr);

    /**
     * @brief Modelクラスから文字列情報を取得する
     * @return 適当な文字列
     */
    Q_INVOKABLE QString getText();

signals:

};

#endif // SCREENA_H
