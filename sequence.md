# 処理シーケンスメモ

-----

## 目次

<!-- @import "[TOC]" {cmd="toc" depthFrom=2 depthTo=6 orderedList=false} -->
<!-- code_chunk_output -->

- [初期化処理](#初期化処理)
- [ボタン押下処理](#ボタン押下処理)

<!-- /code_chunk_output -->

<br>

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


    Model-->>View: return 現在値
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

## ボタン押下処理

```mermaid
---
title: clickedButton()の処理
config:
  theme: neutral
---
sequenceDiagram
    participant View
    participant Model

    activate View
    note over View: 処理開始
    View->>Model: Model.clickedButton()

    deactivate View
    activate Model

    alt 「クリア」ボタン
      Model->>Model: clear()
      note over Model: 現在値のクリア
    else
      Model->>Model: inputNumber()
      note over Model: ボタンの値を<br>現在値の右側に加える
    end

    Model-->>View: return 現在値
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

