#include "namespace_interface.h"
#include "namespace_method.h"

int main() {
  // NAMESPACE内の関数を呼ぶだけ
  uint8_t input = 1;
  bool namespace_ret = NAMESPACE::namespace_sample01(input);

  // インタフェース経由でNAMESPACE内の関数を呼ぶ
  NamespaceInterface namespace_interface;
  bool namespace_via_if_ret = namespace_interface.namespace_sample01(input);

  return 0;
}