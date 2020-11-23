#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Target method: privateMethod01
// Mock method: privateMethod02

// To avoid multiply declaration
namespace UNITTEST {
namespace PRIVATEMETHOD01 {

// Function pointer to replace internal/shared method
typedef void (*privateMethod02_ptr_type)(const uint8_t input, uint8_t &output);

// Add parameter as function pointer to test target
#define privateMethod01(a, b) privateMethod01(a, b, privateMethod02_ptr_type privateMethod02)

#include "../shared_functions.cpp"
#include "../functions.cpp"

// Undefine macro to avoid affect test code
#undef privateMethod01

using ::testing::AtLeast;
using ::testing::SetArgReferee;
using ::testing::_;

// Mock class
class MockPrivate {
 public:
    MOCK_METHOD2(privateMethod02, void(const uint8_t input, uint8_t &output));
};
MockPrivate *mock;

// Mock function
void mockPrivateMethod02(const uint8_t input, uint8_t &output) {
    std::cout << "mock private method called!!" << std::endl;
    return mock->privateMethod02(input, output);
}

class PrivateMethod01Test : public ::testing::Test {
protected:
    // Mock target (private function)
    privateMethod02_ptr_type privateMethod02_ptr;
    virtual void SetUp() {
        mock = new MockPrivate;
        // Overwrite function pointer by Mock
        privateMethod02_ptr = mockPrivateMethod02;
    }
    virtual void TearDown() {
        // Restore original function pointer
        privateMethod02_ptr = privateMethod02;

        delete mock;
    }
};

TEST_F(PrivateMethod01Test, test_no_03) {
    std::cout << "privateMethod01 test start!" << std::endl;
    uint8_t input = 3;
    uint8_t output = 0;

    // Set behavior for Mock
    EXPECT_CALL(*mock, privateMethod02(_, _))
        .Times(1)
        .WillOnce(SetArgReferee<1>(input));

    // evaluation
    // No.1
    privateMethod01(input, output, privateMethod02_ptr);
    EXPECT_EQ(3, output);
}
} // namespace PRIVATEMETHOD01
} // namespace UNITTEST