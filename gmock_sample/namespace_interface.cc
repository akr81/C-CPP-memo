// namespaceで区切ったグローバル関数を呼び出すIFクラス
#include "namespace_interface.h"

#include <stdint.h>

#include <iostream>

bool NamespaceInterface::namespace_sample01(uint8_t input) {
  std::cout << "interface namespace_sample01 called." << std::endl;
  return NAMESPACE::namespace_sample01(input);
}
