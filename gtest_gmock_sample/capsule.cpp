#include "capsule.h"

// Prototype for private function
static void privateMethod01(const uint8_t input, uint8_t &output);

// Implement for public function
void publicMethod(const uint8_t input, uint8_t &output) {
    std::cout << "publicMethod called." << std::endl;

    // call private function
    privateMethod01(input, output);

    return;
}

// Implement for private function
static void privateMethod01(const uint8_t input, uint8_t &output) {
    std::cout << "privateMethod called." << std::endl;

    output = input;
    return;
}
