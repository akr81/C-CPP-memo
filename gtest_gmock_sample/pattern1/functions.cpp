#include "functions.h"
#include "shared_functions.h"

// Prototype for private function
static void privateMethod01(const uint8_t input, uint8_t &output);
static void privateMethod02(const uint8_t input, uint8_t &output);

// Implement for public function
void publicMethod(const uint8_t input, uint8_t &output) {
    std::cout << "publicMethod called." << std::endl;

    // call shared function
    sharedMethod01(input, output);

    // call private function
    privateMethod01(input, output);

    return;
}

// Implement for private function
static void privateMethod01(const uint8_t input, uint8_t &output) {
    std::cout << "privateMethod01 called." << std::endl;

    output = input;
    privateMethod02(input, output);
    return;
}
static void privateMethod02(const uint8_t input, uint8_t &output) {
    std::cout << "privateMethod02 called." << std::endl;
    sharedMethod01(input, output);
    output = input;
    return;
}
