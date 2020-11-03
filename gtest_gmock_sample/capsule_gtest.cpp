#include <gtest/gtest.h>
#include <gmock/gmock.h>

// To avoid multiply declaration
namespace UNITTEST {

// Function pointer to replace internal method
typedef void (*privateMethod01_type)(const uint8_t input, uint8_t &output);

// Add parameter as function pointer to test target
#define publicMethod(a, b) publicMethod(a, b, privateMethod01_type privateMethod01)

#include "capsule.cpp"

// Undefine macro to avoid affect test code
#undef publicMethod

using ::testing::AtLeast;
using ::testing::SetArgReferee;
using ::testing::_;

// Mock class
class MockPrivate {
 public:
    MOCK_METHOD2(privateMethod01, void(const uint8_t input, uint8_t &output));
};
MockPrivate *mock;

// Mock function
void mockPrivateMethod01(const uint8_t input, uint8_t &output) {
    std::cout << "mock private method called!!" << std::endl;
    return mock->privateMethod01(input, output);
}

class SampleTest : public ::testing::Test {
protected:
    // Mock target (private function)
    privateMethod01_type privateMethod01_ptr;
    virtual void SetUp() {
        mock = new MockPrivate;
        // Overwrite function pointer by Mock
        privateMethod01_ptr = mockPrivateMethod01;
    }
    virtual void TearDown() {
        // Restore original function pointer
        privateMethod01_ptr = privateMethod01;

        delete mock;
    }
};

TEST_F(SampleTest, test_no_01) {
    std::cout << "test start!" << std::endl;
    uint8_t input = 3;
    uint8_t output = 0;

    // Set behavior for Mock
    EXPECT_CALL(*mock, privateMethod01(_, _))
        .Times(1)
        .WillOnce(SetArgReferee<1>(input));

    // evaluation
    // No.1
    publicMethod(input, output, privateMethod01_ptr);
    EXPECT_EQ(3, output);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
} // namespace UNITTEST