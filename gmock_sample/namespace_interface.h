// namespaceで区切ったグローバル関数を呼び出すIFクラス
#include <stdint.h>

#include <iostream>

#include "namespace_method.h"

#ifndef NAME_SPACE_INTERFACE_H_
#define NAME_SPACE_INTERFACE_H_

// 抽象クラス
class NamespaceInterface {
 public:
  virtual bool namespace_sample01(uint8_t input) = 0;
};

// 具象クラス
class UseNamespaceInterface : public NamespaceInterface {
 public:
  virtual bool namespace_sample01(uint8_t input);
};

#endif  // NAME_SPACE_INTERFACE_H_