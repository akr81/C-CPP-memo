#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../sample_class.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Return;
using ::testing::SetArgReferee;

// Mock class
class MockClass : public Sample {
 public:
  MOCK_METHOD1(PrivateProcess, uint8_t(const SampleStruct &sample_struct));
};

class PublicMethodTest : public ::testing::Test {
 protected:
  MockClass *mock;
  virtual void SetUp() {
    mock = new MockClass;
  }
    virtual void TearDown() {
    delete mock;
  }
};

// define MATCHER
MATCHER_P(sample_match, expected, "") {
  return (arg.member1 == expected.member1) && (arg.member2 == expected.member2);
}

TEST_F(PublicMethodTest, test_no_01) {
  std::cout << "StructReceiver test start!" << std::endl;
  SampleStruct sample_struct{4U, 7U};
  SampleStruct expected_struct{4U, 7U};


  // Set behavior for Mock
  // Check input struct members, number of called and return value.
  EXPECT_CALL(*mock, PrivateProcess(sample_match(expected_struct)))
    .Times(1)
    .WillOnce(Return(4));

  // evaluation
  // No.1
  uint8_t ret = mock->StructReceiver(sample_struct);
  EXPECT_EQ(4, ret);
}

int main(int argc, char** argv) {
  // 以下の行は，テスト開始前に Google Mock （と Google Test）
  // を初期化するために必ず実行する必要があります．
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
