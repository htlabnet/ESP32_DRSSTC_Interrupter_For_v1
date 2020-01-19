#ifndef LIB_OUTPUT_H
#define LIB_OUTPUT_H

#include <Arduino.h>
#include <SPI.h>


// IO-Expander Register Map
#define EXP_ADDR 0x40
#define EXP_REG_DIR 0x00
#define EXP_REG_GPIO 0x09


void expInit(SPIClass &spi, uint8_t ss);
void expPinWrite(SPIClass &spi, uint8_t ss, uint8_t pin, bool state);

void spiLcdBegin(SPIClass &spi, uint8_t cs, uint8_t rs, uint8_t ena, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
size_t spiLcdPrintChar(const char *buffer);
size_t spiLcdPrint(const String &s);
size_t spiLcdPrint(const char str[]);
void spiLcdCreateChar(uint8_t location, uint8_t charmap[]);
void spiLcdCustomChar(uint8_t id);
void spiLcdClear();
void spiLcdHome();
void spiLcdSetCursor(uint8_t col, uint8_t row);
void spiLcdNoDisplay();
void spiLcdDisplay();
inline void spiLcdCommand(uint8_t value);
inline size_t spiLcdWrite(uint8_t value);
void spiLcdSend(uint8_t value, uint8_t mode);
void spiLcdEnable(void);
void spiLcdWrite4Bit(uint8_t value);


#endif
