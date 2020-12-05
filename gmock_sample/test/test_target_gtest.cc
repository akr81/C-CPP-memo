#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../test_target.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Return;
using ::testing::SetArgReferee;

// Mock class for target
class MockTestTarget : public TestTarget {
 public:
  // ベースクラスのコンストラクタ呼び出し
  MockTestTarget(NamespaceInterface& ptr) : TestTarget(ptr){};
  MOCK_METHOD1(privateMethod01, bool(uint8_t input));
};
MockTestTarget* mock;

// Mock class for interface
class MockInterface : public NamespaceInterface {
 public:
  MOCK_METHOD1(namespace_sample01, bool(uint8_t input));
};
MockInterface* mock_interface;

// Test class
class PublicMethodTest : public ::testing::Test {
 protected:
  // MockInterface mock_interface;
  virtual void SetUp() {
    mock_interface = new MockInterface();
    mock = new MockTestTarget(*mock_interface);
  }
  virtual void TearDown() {
    delete mock;
    delete mock_interface;
  }
};

TEST_F(PublicMethodTest, test_no_01) {
  std::cout << "publicMethod test start!" << std::endl;
  uint8_t input = 3;

  // Set behavior for Mock
  EXPECT_CALL(*mock, privateMethod01(_)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*mock_interface, namespace_sample01(_)).Times(1);

  // evaluation
  // No.1
  bool ret = mock->publicMethod(input);
  EXPECT_EQ(true, ret);
}
