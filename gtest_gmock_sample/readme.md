# Cコードのgtest/gmock適用サンプル
## はじめに
クラス等を使わないCコード(拡張子はcppにしてしまいましたが)にgtest/gmockを適用するサンプルです。  
想定している条件は以下の通りです。

- 既存のソースコードは可能な限り変更しない
- ソースコードに対して関数単位でテストをしたい
- テスト対象の関数から呼ばれる関数はスタブ(モック)化したい
- テスト対象の関数が同一ファイル内の別関数から呼び出されている


## サンプル説明
参考ページのアイデアを勉強がてら実装してみたものです。  

### 環境
以下の環境で動作を確認しています。

- WSL on Windows10
- Python 3.6.9

### Pattern1: テスト対象関数に関数ポインタ引数を追加
ファイルの構成は以下の通りです。
```
./pattern1
├── Makefile
├── functions.cpp
├── functions.h
├── main.cpp
├── preprocess_and_fix.py
├── shared_functions.cpp
├── shared_functions.h
└── test
    ├── privateMethod01_gtest.cpp
    ├── privateMethod02_gtest.cpp
    └── publicMethod_gtest.cpp
```
- functions.cpp/.h: テスト対象となるコードです。3つのテスト対象関数を含んでいます。
  - `publicMethod`: 外部から直接呼び出される関数です。
  - `privateMethod01`: `publicMethod`から呼び出される関数です。
  - `privateMethod02`: `privateMethod01`から呼び出される関数です。
- main.cpp: メイン関数(`publicMethod`を呼び出すだけ)が書かれています。
- shared_functions.cpp/.h: 様々な場所から呼び出されるユーティリティ的なコードを想定しています。
  - `sharedMethod01`: `publicMethod`, `privateMethod02`から呼び出される関数です。
- Makefile: 後述するいくつかのターゲットが設定されています。
- preprocess_and_fix.py: プリプロセス結果の編集と保存を行います(「仕組み」を参照)。
- test/*gtest.cpp: ファイル名の関数をテストするためのコードです。

#### Makeターゲット
|ターゲット名|概要|
|---|---|
|build|通常のビルドを行います。|
|public|`publicMethod`をテストするためのビルドです。|
|private|`privateMethod01`, `privateMethod02`をテストするためのビルドです。<br>**このターゲットは常にビルド失敗します。**|
|functions|テスト対象関数すべてをテストするためのビルドです。|
|clean|バイナリ、中間ファイルを削除します。|

#### 仕組み
参考ページの[関数ポインタを渡す](https://qiita.com/HAMADA_Hiroshi/items/e1dd3257573ea466d169#%E9%96%A2%E6%95%B0%E3%83%9D%E3%82%A4%E3%83%B3%E3%82%BF%E3%82%92%E6%B8%A1%E3%81%99)を使っています。

ただこの構成では、`publicMethod`のテストはビルドできたものの、`privateMethod01, 02`のテストはビルドエラーとなりました。
これは、関数ポインタを引数として取るように置き換える関数マクロ(テスト対象関数のプロトタイプ宣言と定義が対象)が、テスト対象でない関数内のテスト対象関数呼び出しまで置き換えてしまうため発生します。

`preprocess_and_fix.py`は、プリプロセス結果のうち不要な要素(テスト対象関数呼び出し部の型)を削除します。
今回テストコードは自由に作れる想定であるため、関数ポインタ型名の末尾に`ptr_type`が付与されていることを前提としています。

### Pattern2: テスト対象関数から呼び出す関数に行番号を付与
TBD

## 参考
- [C言語のテストでスタブ関数を使うためのアイデア](https://qiita.com/HAMADA_Hiroshi/items/e1dd3257573ea466d169)