#include "sample_struct.h"

int main() {
  SimpleStruct data;
  data.member_int01 = 123;
  data.member_int02 = -123;
  data.member_int03 = 456;
  data.member_uint8 = 234;
  data.member_uint16 = 23456;
  data.member_uint32 = 123456;
  data.member_uint64 = 2;
  data.member_size = 234;
  data.member_bool01 = true;
  data.member_double01 = 1.2345;

  data.inner.inner01 = -1.2345;
  data.inner.inner02 = 4567;

  // 構造体をダンプ出力
  std::fstream file("./dumpout.dat", std::ios::binary | std::ios::out);
  file.write((char*)&data, sizeof(data));
  file.close();
}