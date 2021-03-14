#include "sample_struct.h"

// dll作成のためのサンプル
/**
 * @brief FillDumpData
 * 引数で指定された構造体にダンプデータを詰め込む
 * @param [in, out] simple_struct
 */
// extern "C"を付与しないとシンボル名が変わってしまい呼び出せなくなる
extern "C" __attribute__((visibility("default"))) void FillDumpData(SimpleStruct &simple_struct) {
  // ダンプデータを読み込んで引数変数にコピー
  std::fstream file;
  file.open("./dumpout.dat", std::ios::binary | std::ios::in);
  file.read((char*)&simple_struct, sizeof(simple_struct));
  file.close();
}
