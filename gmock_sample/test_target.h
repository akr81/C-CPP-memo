// テストしたいクラス
#include <stdint.h>

#include <iostream>

#include "gtest/gtest_prod.h"
#include "namespace_interface.h"

#ifndef TEST_TARGET_H_
#define TEST_TARGET_H_

// すべてのメソッドがテスト対象となる
class TestTarget {
 public:
  TestTarget(NamespaceInterface& ptr) : user_interface(ptr){};
  virtual ~TestTarget(){};

  // private01とnamespace_sample01を呼び出す
  virtual bool publicMethod(uint8_t input);

 private:
  // private02を呼び出す
  virtual bool privateMethod01(uint8_t input);

  // namespace_sample01を呼び出す
  virtual bool privateMethod02(uint8_t input);

  // 抽象クラスの参照：コンストラクタにて具象クラスで初期化する
  NamespaceInterface& user_interface;

  FRIEND_TEST(PublicMethodTest, test_no_01);
};

#endif  // TEST_TARGET_H_