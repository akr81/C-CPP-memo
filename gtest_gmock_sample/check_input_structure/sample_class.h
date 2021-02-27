#include <stdint.h>
#include <iostream>
#include <algorithm>

#ifndef CHECK_INPUT_STRUCTURE_SAMPLE_CLASS_H_
#define CHECK_INPUT_STRUCTURE_SAMPLE_CLASS_H_

// struct definition
struct SampleStruct {
  uint8_t member1;
  uint8_t member2;
};

// sample class
class Sample {
 public:
  Sample() {}
  virtual ~Sample() {}

  uint8_t StructReceiver(const SampleStruct &sample_struct) {
    std::cout << "actual StructReceiver called!!" << std::endl;
    return PrivateProcess(sample_struct);
  }

 private:
  virtual uint8_t PrivateProcess(const SampleStruct &sample_struct) {
    std::cout << "actual PrivateProcess called!!" << std::endl;
    uint8_t min = std::min(sample_struct.member1, sample_struct.member2);
    return min;
  }
FRIEND_TEST(PublicMethodTest, test_no_01);
};


#endif  // CHECK_INPUT_STRUCTURE_SAMPLE_CLASS_H_
