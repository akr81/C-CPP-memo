#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../namespace_interface.h"

// NamespaceInterfaceクラスのメソッドをモック化する
using ::testing::_;
using ::testing::AtLeast;
using ::testing::Return;
using ::testing::SetArgReferee;

// Mock class
class MockPrivate : public NamespaceInterface {
 public:
  MOCK_METHOD1(namespace_sample01, bool(uint8_t input));
};
MockPrivate *mock;

class PublicMethodTest : public ::testing::Test {
 protected:
  virtual void SetUp() { mock = new MockPrivate; }
  virtual void TearDown() { delete mock; }
};

TEST_F(PublicMethodTest, test_no_01) {
  std::cout << "publicMethod test start!" << std::endl;
  uint8_t input = 3;

  // Set behavior for Mock
  EXPECT_CALL(*mock, namespace_sample01(_)).Times(1).WillOnce(Return(true));

  // evaluation
  // No.1
  MockPrivate interface;
  bool ret = interface.namespace_sample01(input);
  EXPECT_EQ(true, ret);
}
