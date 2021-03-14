# 構造体データのダンプ出力と読み込み

構造体データをバイナリ出力し、別のプログラムから読み込んでみる。

## 概要
```puml
left to right direction 
agent "dump_sample.cc" as dump_sample
note bottom : 構造体にデータを格納
agent "sample_struct.h" as struct
note bottom : 扱いたい構造体
agent "dumpout.dat" as dump_data
agent "read_sample.cc" as read_sample
note bottom : ダンプデータを読み込んで\n表示する処理を実装
agent "reader" as exe_file
agent "display" as display

usecase "ビルド&実行" as store
usecase "ビルド" as build
usecase "reader実行" as exe_reader

dump_sample --> store
struct --> store
store --> dump_data : ダンプデータ出力

read_sample --> build
struct --> build
build --> exe_file

exe_file --> exe_reader
dump_data --> exe_reader : 実行時に読み込み
exe_reader --> display : 表示
```

## 実行方法
- dump_sample.ccをビルドして実行する。
  ```
  g++ dump_sample.cc
  ./a.out
  ```
- dumpout.datが出力されていることを確認する。
- read_sample.ccをビルドして実行する。
  ```
  g++ read_sample.cc
  ./a.out
  ```
- dump_sample.ccで格納した値が表示されることを確認する。