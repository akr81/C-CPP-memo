#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Target method: privateMethod02
// Mock method: sharedMethod01

// To avoid multiply declaration
namespace UNITTEST {
namespace PRIVATEMETHOD02 {

// Function pointer to replace internal/shared method
typedef void (*sharedMethod01_ptr_type)(const uint8_t input, uint8_t &output);

// Add parameter as function pointer to test target
#define privateMethod02(a, b) privateMethod02(a, b, sharedMethod01_ptr_type sharedMethod01)

#include "../shared_functions.cpp"
#include "../functions.cpp"

// Undefine macro to avoid affect test code
#undef privateMethod02

using ::testing::AtLeast;
using ::testing::SetArgReferee;
using ::testing::_;

// Mock class
class MockPrivate {
 public:
    MOCK_METHOD2(sharedMethod01, void(const uint8_t input, uint8_t &output));
};
MockPrivate *mock;

// Mock function
void mockSharedMethod01(const uint8_t input, uint8_t &output) {
    std::cout << "mock shared method called!!" << std::endl;
    return mock->sharedMethod01(input, output);
}

class PrivateMethod02Test : public ::testing::Test {
protected:
    // Mock target (private function)
    sharedMethod01_ptr_type sharedMethod01_ptr;
    virtual void SetUp() {
        mock = new MockPrivate;
        // Overwrite function pointer by Mock
        sharedMethod01_ptr = mockSharedMethod01;
    }
    virtual void TearDown() {
        // Restore original function pointer
        sharedMethod01_ptr = sharedMethod01;

        delete mock;
    }
};

TEST_F(PrivateMethod02Test, test_no_02) {
    std::cout << "privateMethod02 test start!" << std::endl;
    uint8_t input = 3;
    uint8_t output = 0;

    // Set behavior for Mock
    EXPECT_CALL(*mock, sharedMethod01(_, _))
        .Times(1)
        .WillOnce(SetArgReferee<1>(input));

    // evaluation
    // No.1
    privateMethod02(input, output, sharedMethod01_ptr);
    EXPECT_EQ(3, output);
}
} // namespace PRIVATEMETHOD02
} // namespace UNITTEST