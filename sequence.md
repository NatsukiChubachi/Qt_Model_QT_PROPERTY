# 処理シーケンスメモ

-----

## 目次

<!-- @import "[TOC]" {cmd="toc" depthFrom=2 depthTo=6 orderedList=false} -->
<!-- code_chunk_output -->

- [状態遷移図](#状態遷移図)
- [状態変化通知](#状態変化通知)
- [初期化処理](#初期化処理)
- [入金ボタン押下処理](#入金ボタン押下処理)
- [商品ボタン押下処理](#商品ボタン押下処理)
- [取り消しボタン押下処理](#取り消しボタン押下処理)

<!-- /code_chunk_output -->

<br>

-----

## 状態遷移図

```mermaid
---
title: 状態遷移図
config:
  theme: neutral
---
graph LR
    Start((" ")) --> A[初期化状態]
    A -- 初期化完了 --> B[アイドル状態]
    B -- 現在金額が0以上 --> C[入金中状態]
    C -- 「取り消し」ボタン押下 --> D[取消手続中状態] 
    C -- 「商品」ボタン押下 --> E[購入手続中状態]
    D -- 手続完了 --> B
    E -- 現在金額が0 --> B
    E -- 現在金額が0以上 --> C
```

<br>
<br>

[目次へ](#目次)

-----

## 状態変化通知

```mermaid
---
title: 状態値の変化通知処理
config:
  theme: neutral
---
sequenceDiagram
    participant View
    participant Model

    activate Model
    note over Model: 状態値の更新
    
    Model-->>View: sigChangedExecState() <br>状態変化通知
    deactivate Model
    activate View

    note over View: 通知された状態を<br>画面へ反映
    note over View: 処理完了
    deactivate View
```

<br>
<br>

[目次へ](#目次)

-----

## 初期化処理

```mermaid
---
title: Component.onComplete()の処理
config:
  theme: neutral
---
sequenceDiagram
    participant View
    participant Model

    activate View
    note over View: 処理開始
    View->>Model: Model.initialize()

    deactivate View
    activate Model

    Model->>Model: clear()
    note over Model: 現在値のクリア

    note over Model: 状態値の更新 <br>(アイドル状態(1))

    Model->>View: return 現在値
    deactivate Model
    activate View

    note over View: 現在値を画面へ反映
    note over View: 処理完了
    deactivate View
```

<br>
<br>

[目次へ](#目次)

-----

## 入金ボタン押下処理

```mermaid
---
title: clickedButtonCoin()の処理
config:
  theme: neutral
---
sequenceDiagram
    participant View
    participant Model

    activate View
    note over View: 処理開始
    View->>Model: Model.clickedButtonCoin()

    deactivate View
    activate Model

    alt 現在金額が0円の場合
      note over Model: 状態値の更新 <br>(入金中状態(2))
    end

    note over Model: 現在金額の加算

    Model->>View: return 現在値
    deactivate Model
    activate View

    note over View: 現在値を画面へ反映
    note over View: 処理完了
    deactivate View
```

<br>
<br>

[目次へ](#目次)

-----

## 商品ボタン押下処理

```mermaid
---
title: clickedButtonMerchandise()の処理
config:
  theme: neutral
---
sequenceDiagram
    participant View
    participant Model

    activate View
    note over View: 処理開始
    View->>Model: Model.clickedButtonMerchandise()

    deactivate View
    activate Model

    note over Model: 状態値の更新 <br>(購入手続中状態(4))

    note over Model: 現在金額から<br>商品金額分をマイナスする

    Model->>View: return 現在値
    activate View

    note over View: 現在値を画面へ反映

    alt 現在金額が0円
      note over Model: 状態値の更新 <br>(アイドル状態(1))
    else
      note over Model: 状態値の更新 <br>(入金中状態(2))
    end
    deactivate Model

    note over View: 処理完了
    deactivate View
```

<br>
<br>

[目次へ](#目次)

-----

## 取り消しボタン押下処理

```mermaid
---
title: clickedButtonMerchandise()の処理
config:
  theme: neutral
---
sequenceDiagram
    participant View
    participant Model

    activate View
    note over View: 処理開始
    View->>Model: Model.clickedButtonMerchandise()

    deactivate View
    activate Model

    note over Model: 状態値の更新 <br>(購入手続中状態(4))

    note over Model: 現在金額から<br>商品金額分をマイナスする

    Model->>View: return 現在値
    activate View

    note over View: 現在値を画面へ反映

    alt 現在金額が0円
      note over Model: 状態値の更新 <br>(アイドル状態(1))
    else
      note over Model: 状態値の更新 <br>(入金中状態(2))
    end
    deactivate Model

    note over View: 処理完了
    deactivate View
```

<br>
<br>

[目次へ](#目次)

-----
