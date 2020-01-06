#include "lib_output.h"


void expInit(SPIClass &spi, uint8_t ss) {
  digitalWrite(ss, LOW);
  spi.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
  // Set All Pins OUTPUT
  spi.transfer(EXP_ADDR);
  spi.transfer(EXP_REG_DIR);
  spi.transfer(0x00);
  // Set All Pins LOW
  spi.transfer(EXP_ADDR);
  spi.transfer(EXP_REG_GPIO);
  spi.transfer(0x00);
  spi.endTransaction();
  digitalWrite(ss, HIGH);
  return;
}


void expPinWrite(SPIClass &spi, uint8_t ss, uint8_t pin, bool state) {
  static uint8_t pinState = 0x00;
  digitalWrite(ss, LOW);
  spi.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
  spi.transfer(EXP_ADDR);
  spi.transfer(EXP_REG_GPIO);
  spi.transfer((pinState & ~(1 << pin)) | (state << pin));
  spi.endTransaction();
  digitalWrite(ss, HIGH);
  return;
}
