#include "lib_input.h"


uint16_t adcRead(SPIClass &spi, uint8_t ss, uint8_t ch) {
  digitalWrite(ss, LOW);
  spi.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  spi.transfer(((ch & 0b111) >> 2) + 0b110);
  uint8_t dat_h = spi.transfer((ch & 0b11) << 6);
  uint8_t dat_l = spi.transfer(0x00);
  spi.endTransaction();
  digitalWrite(ss, HIGH);
  return ((dat_h & 0b1111) << 8) + dat_l;
}

