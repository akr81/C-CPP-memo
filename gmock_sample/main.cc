#include "namespace_method.h"

int main() {
  // ただ関数を呼ぶだけ
  uint8_t input = 1;
  bool namespace_ret = NAMESPACE::namespace_sample01(input);
  return 0;
}