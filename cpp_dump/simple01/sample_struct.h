#include <iostream>
#include <fstream>

struct InnerStruct {
  float inner01;
  uint16_t inner02;
};

struct SimpleStruct {
  int member_int01;
  int member_int02;
  int member_int03;
  uint8_t member_uint8;
  uint16_t member_uint16;
  uint32_t member_uint32;
  uint64_t member_uint64;
  size_t member_size;
  bool member_bool01;
  double member_double01;

  InnerStruct inner;
};
