#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Target method: publicMethod
// Mock method: privateMethod01, sharedMethod01

// To avoid multiply declaration
namespace UNITTEST {
namespace PUBLICMETHOD {

// Function pointer to replace internal/shared method
typedef void (*privateMethod01_ptr_type)(const uint8_t input, uint8_t &output);
typedef void (*sharedMethod01_ptr_type)(const uint8_t input, uint8_t &output);

// Add parameter as function pointer to test target
#define publicMethod(a, b) publicMethod(a, b, privateMethod01_ptr_type privateMethod01, sharedMethod01_ptr_type sharedMethod01)

#include "../shared_functions.cpp"
#include "../functions.cpp"

// Undefine macro to avoid affect test code
#undef publicMethod

using ::testing::AtLeast;
using ::testing::SetArgReferee;
using ::testing::_;

// Mock class
class MockPrivate {
 public:
    MOCK_METHOD2(privateMethod01, void(const uint8_t input, uint8_t &output));
    MOCK_METHOD2(sharedMethod01, void(const uint8_t input, uint8_t &output));
};
MockPrivate *mock;

// Mock function
void mockPrivateMethod01(const uint8_t input, uint8_t &output) {
    std::cout << "mock private method called!!" << std::endl;
    return mock->privateMethod01(input, output);
}
void mockSharedMethod01(const uint8_t input, uint8_t &output) {
    std::cout << "mock shared method called!!" << std::endl;
    return mock->sharedMethod01(input, output);
}

class PublicMethodTest : public ::testing::Test {
protected:
    // Mock target (private function)
    privateMethod01_ptr_type privateMethod01_ptr;
    sharedMethod01_ptr_type sharedMethod01_ptr;
    virtual void SetUp() {
        mock = new MockPrivate;
        // Overwrite function pointer by Mock
        privateMethod01_ptr = mockPrivateMethod01;
        sharedMethod01_ptr = mockSharedMethod01;
    }
    virtual void TearDown() {
        // Restore original function pointer
        privateMethod01_ptr = privateMethod01;
        sharedMethod01_ptr = sharedMethod01;

        delete mock;
    }
};

TEST_F(PublicMethodTest, test_no_01) {
    std::cout << "publicMethod test start!" << std::endl;
    uint8_t input = 3;
    uint8_t output = 0;

    // Set behavior for Mock
    EXPECT_CALL(*mock, sharedMethod01(_, _))
        .Times(1)
        .WillOnce(SetArgReferee<1>(input));
    EXPECT_CALL(*mock, privateMethod01(_, _))
        .Times(1)
        .WillOnce(SetArgReferee<1>(input));

    // evaluation
    // No.1
    publicMethod(input, output, privateMethod01_ptr, sharedMethod01_ptr);
    EXPECT_EQ(3, output);
}
} // namespace PUBLICMETHOD
} // namespace UNITTEST