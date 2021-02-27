#include "sample_class.h"

// Main function
// Used all build only
int main() {

  SampleStruct sample_struct{3U, 5U};
  Sample sample;
  uint8_t ret = sample.StructReceiver(sample_struct);

  std::cout << "Returned: " << static_cast<uint16_t>(ret) << std::endl;

  return 0;
}
