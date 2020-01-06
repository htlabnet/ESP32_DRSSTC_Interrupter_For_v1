#ifndef LIB_OUTPUT_H
#define LIB_OUTPUT_H

#include <Arduino.h>
#include <SPI.h>
#include "settings.h"


void expInit(SPIClass &spi, uint8_t ss);
void expPinWrite(SPIClass &spi, uint8_t ss, uint8_t pin, bool state);


#endif
