// namespaceで区切るだけのグローバル関数

#include "namespace_method.h"

namespace NAMESPACE {
bool namespace_sample01(uint8_t input) {
  std::cout << "actual namespace_sample01 calld." << std::endl;
  bool ret = (input == 1);
  return ret;
}
}  // namespace NAMESPACE