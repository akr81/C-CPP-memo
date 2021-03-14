# 構造体データのダンプ出力とPythonからの読み込み

構造体データをバイナリ出力し、Pythonからライブラリを使って読み込んでみる。
Pythonでは構造体情報の処理にループを利用できるため、加工がしやすくなる。

## 概要
```puml
left to right direction 
agent "dump_sample.cc" as dump_sample
note bottom : 構造体にデータを格納
agent "sample_struct.h" as struct
note bottom : 扱いたい構造体
agent "dumpout.dat" as dump_data
agent "dll_sample.cc" as dll_sample
note bottom : ダンプデータを読み込んで\n値格納するAPIを実装
agent "dll_sample.dll" as dll

rectangle "dump_reader.py" as reader {
agent "構造体の情報" as struct_info
}
cloud "ctypes library" as ctypes
agent "構造体の内容" as display

usecase "ビルド&実行" as store
usecase "dll作成" as make_dll
usecase "dump_reader実行" as exe_reader

dump_sample --> store
struct --> store
store --> dump_data : ダンプデータ出力

dll_sample --> make_dll
struct --> make_dll
make_dll --> dll

reader --> exe_reader
ctypes --> exe_reader : import
dll --> exe_reader : ctypesから利用
dump_data --> exe_reader : dllから読み込み
struct ..> struct_info : 構造体の構成を記述
exe_reader --> display : 表示
```

## 実行方法
- dump_sample.ccをビルドして実行する。
  ```
  g++ dump_sample.cc
  ./a.out
  ```
- dumpout.datが出力されていることを確認する。
- dll_sample.ccをビルドしてdllを作成する。
  ```
  g++ -c ./dll_sample.cc -fPIC
  g++ -shared dll_sample.o -o dll_sample.dll
  ```
- dump_reader.pyで格納した値が表示されることを確認する。
  ```
  python dump_reader.py
  ```

  ## 参考
  以下を参考にさせていただきました。
  - [CとC++が混在したプログラムでの注意点](https://qiita.com/nomunomu0504/items/722a2771fef7d8038ceb)
  - [PythonからDLL(ダイナミックリンクライブラリ)を利用する](https://bluebirdofoz.hatenablog.com/entry/2019/11/16/220553)