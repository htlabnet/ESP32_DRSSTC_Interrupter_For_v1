#ifndef LIB_INPUT_H
#define LIB_INPUT_H

#include <Arduino.h>
#include <SPI.h>


uint16_t adcRead(SPIClass &spi, uint8_t ss, uint8_t ch);


#endif
