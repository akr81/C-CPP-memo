// テストしたいクラス
#include "test_target.h"

#include <stdint.h>

#include <iostream>

bool TestTarget::publicMethod(uint8_t input) {
  bool ret1 = privateMethod01(input);
  // namespaceで切られた関数を呼び出し
  bool ret2 = NAMESPACE::namespace_sample01(input);
  // インスタンス作成しInterface経由で呼び出し
  UseNamespaceInterface interface;
  bool ret3 = interface.namespace_sample01(input);
  // メンバ変数のInterface経由で呼び出し
  bool ret4 = user_interface.namespace_sample01(input);

  return (ret1 && ret2 && ret3 && ret4);
}

bool TestTarget::privateMethod01(uint8_t input) { return true; }

bool TestTarget::privateMethod02(uint8_t input) { return true; }
