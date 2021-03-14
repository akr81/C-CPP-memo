#include "sample_struct.h"

int main() {
  SimpleStruct data;

  // ダンプデータを読み込んでコピー
  std::fstream file;
  file.open("./dumpout.dat", std::ios::binary | std::ios::in);
  file.read((char*)&data, sizeof(data));
  file.close();

  std::cout << data.member_int01 << std::endl;
  std::cout << data.member_int02 << std::endl;
  std::cout << data.member_int03 << std::endl;
  std::cout << static_cast<uint16_t>(data.member_uint8) << std::endl;
  std::cout << data.member_uint16 << std::endl;
  std::cout << data.member_uint32 << std::endl;
  std::cout << data.member_uint64 << std::endl;
  std::cout << data.member_size << std::endl;
  std::cout << data.member_bool01 << std::endl;
  std::cout << data.member_double01 << std::endl;
  std::cout << data.inner.inner01 << std::endl;
  std::cout << data.inner.inner02 << std::endl;
}