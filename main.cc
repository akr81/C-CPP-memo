#include <cstdint>

#include "csv_logger.h"

// add variable to variable name
#define addItem(a) addItem(a, #a)

int main() {
  for (size_t i = 0; i < 3; ++i) {
    bool bool_in = ((i % 2) == 0);
    uint8_t uint8_in = 1 * i;
    uint16_t uint16_in = 1 * i;
    int8_t int8_in = -1 * i;
    float float_in = 1.23 * i;
    double double_in = 1.2345678 * i;
    CsvLogger logger;
    logger.addItem(bool_in);
    logger.addItem(uint8_in);
    logger.addItem(uint16_in);
    logger.addItem(int8_in);
    logger.addItem(float_in);
    logger.addItem(double_in);

    logger.writeLog("./test.csv");
  }
}