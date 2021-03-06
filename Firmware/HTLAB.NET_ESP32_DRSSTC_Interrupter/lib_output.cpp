#include "lib_output.h"


SPIClass _spiLcdSpi;
uint8_t _spiLcdExpCS;
uint8_t _spiLcdRS;
uint8_t _spiLcdENA;
uint8_t _spiLcdDB4;
uint8_t _spiLcdDB5;
uint8_t _spiLcdDB6;
uint8_t _spiLcdDB7;
uint8_t _row_offsets[4];


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
  pinState = (pinState & ~(1 << pin)) | (state << pin);
  digitalWrite(ss, LOW);
  spi.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
  spi.transfer(EXP_ADDR);
  spi.transfer(EXP_REG_GPIO);
  spi.transfer(pinState);
  spi.endTransaction();
  digitalWrite(ss, HIGH);
  return;
}

  
void spiLcdBegin(SPIClass &spi, uint8_t cs, uint8_t rs, uint8_t ena, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) {
  _spiLcdSpi = spi;
  _spiLcdExpCS = cs;
  _spiLcdRS = rs;
  _spiLcdENA = ena;
  _spiLcdDB4 = d4;
  _spiLcdDB5 = d5;
  _spiLcdDB6 = d6;
  _spiLcdDB7 = d7;
  _row_offsets[0] = 0b00000000;
  _row_offsets[1] = 0b01000000;
  _row_offsets[2] = 0b00000000 + 20;
  _row_offsets[3] = 0b01000000 + 20;

  // Initialization
  delayMicroseconds(50000);
  expPinWrite(_spiLcdSpi, _spiLcdExpCS, _spiLcdRS, LOW);
  expPinWrite(_spiLcdSpi, _spiLcdExpCS, _spiLcdENA, LOW);

  // Function Set (8-bit mode)
  spiLcdWrite4Bit(0b0011);
  delayMicroseconds(4500);

  // Function Set (8-bit mode)
  spiLcdWrite4Bit(0b0011);
  delayMicroseconds(4500);

  // Function Set (8-bit mode)
  spiLcdWrite4Bit(0b0011);
  delayMicroseconds(150);

  // Function Set (4-bit mode)
  spiLcdWrite4Bit(0b0010);

  // Function Set
  spiLcdCommand(0b00101000);

  // Display ON
  spiLcdDisplay();

  // Clear
  spiLcdClear();

  // Entry Mode
  spiLcdCommand(0b00000110);
}


void spiLcdClear() {
  spiLcdCommand(0b00000001);
  delayMicroseconds(2000);
}


void spiLcdHome() {
  spiLcdCommand(0b00000010);
  delayMicroseconds(2000);
}


void spiLcdSetCursor(uint8_t col, uint8_t row) {
  spiLcdCommand(0b10000000 | (col + _row_offsets[row]));
}


void spiLcdNoDisplay() {
  spiLcdCommand(0b00001000);
}


void spiLcdDisplay() {
  spiLcdCommand(0b00001100);
}


size_t spiLcdPrintChar(const char *buffer) {
  size_t n = 0;
  size_t size = strlen(buffer);
  while (size--) {
    if (spiLcdWrite(*buffer++)) n++;
    else break;
  }
  return n;
}


size_t spiLcdPrint(const String &s) {
  return spiLcdPrintChar(s.c_str());
}


size_t spiLcdPrint(const char str[]) {
  return spiLcdPrintChar(str);
}


void spiLcdCreateChar(uint8_t location, uint8_t charmap[]) {
  location &= 0b00000111;
  spiLcdCommand(0b01000000 | (location << 3));
  for (int i=0; i<8; i++) {
    spiLcdWrite(charmap[i]);
  }
}


void spiLcdCustomChar(uint8_t id) {
  if (id >= 8) return;
  spiLcdWrite(id);
}


inline void spiLcdCommand(uint8_t value) {
  spiLcdSend(value, LOW);
}


inline size_t spiLcdWrite(uint8_t value) {
  spiLcdSend(value, HIGH);
  return 1;
}


void spiLcdSend(uint8_t value, uint8_t mode) {
  expPinWrite(_spiLcdSpi, _spiLcdExpCS, _spiLcdRS, mode);
  spiLcdWrite4Bit(value >> 4);
  spiLcdWrite4Bit(value);
}


void spiLcdEnable(void) {
  expPinWrite(_spiLcdSpi, _spiLcdExpCS, _spiLcdENA, LOW);
  delayMicroseconds(1);
  expPinWrite(_spiLcdSpi, _spiLcdExpCS, _spiLcdENA, HIGH);
  delayMicroseconds(1);
  expPinWrite(_spiLcdSpi, _spiLcdExpCS, _spiLcdENA, LOW);
  delayMicroseconds(100);
}


void spiLcdWrite4Bit(uint8_t value) {
  expPinWrite(_spiLcdSpi, _spiLcdExpCS, _spiLcdDB4, (value >> 0) & 0x01);
  expPinWrite(_spiLcdSpi, _spiLcdExpCS, _spiLcdDB5, (value >> 1) & 0x01);
  expPinWrite(_spiLcdSpi, _spiLcdExpCS, _spiLcdDB6, (value >> 2) & 0x01);
  expPinWrite(_spiLcdSpi, _spiLcdExpCS, _spiLcdDB7, (value >> 3) & 0x01);
  spiLcdEnable();
}


void pulsePin(uint8_t ch, uint8_t pin) {
  ledcAttachPin(pin, ch);
}


void IRAM_ATTR pulseOut(uint8_t ch, uint16_t hz, uint16_t us) {

/*
 * LEDC Chan to Group/Channel/Timer Mapping
** ledc: 0  => Group: 0, Channel: 0, Timer: 0
** ledc: 1  => Group: 0, Channel: 1, Timer: 0
** ledc: 2  => Group: 0, Channel: 2, Timer: 1
** ledc: 3  => Group: 0, Channel: 3, Timer: 1
** ledc: 4  => Group: 0, Channel: 4, Timer: 2
** ledc: 5  => Group: 0, Channel: 5, Timer: 2
** ledc: 6  => Group: 0, Channel: 6, Timer: 3
** ledc: 7  => Group: 0, Channel: 7, Timer: 3
** ledc: 8  => Group: 1, Channel: 0, Timer: 0
** ledc: 9  => Group: 1, Channel: 1, Timer: 0
** ledc: 10 => Group: 1, Channel: 2, Timer: 1
** ledc: 11 => Group: 1, Channel: 3, Timer: 1
** ledc: 12 => Group: 1, Channel: 4, Timer: 2
** ledc: 13 => Group: 1, Channel: 5, Timer: 2
** ledc: 14 => Group: 1, Channel: 6, Timer: 3
** ledc: 15 => Group: 1, Channel: 7, Timer: 3
*/

  static uint16_t last_hz[16];
  static uint16_t last_us[16];
  static uint8_t last_bit[16];
  uint8_t bit_num;
  double base_num;

  if (hz <= 4) {
    ledcWrite(ch, 0);
    last_hz[ch] = hz;
    return;
  } else if (hz <= 305) {
    bit_num = 18;
    base_num = 3.75;
  } else if (hz <= 610) {
    bit_num = 17;
    base_num = 7.5;
  } else if (hz <= 1220) {
    bit_num = 16;
    base_num = 15.0;
  } else if (hz <= 2441) {
    bit_num = 15;
    base_num = 30.0;
  } else if (hz <= 4882) {
    bit_num = 14;
    base_num = 60.0;
  }
  uint32_t period = ((double)hz * (double)us) / base_num;

  if ((500000 / hz) <= us) {
    // Max 50% Duty
    return;
  }

  if (last_hz[ch] < hz) {
    ledcSetup(ch, hz, bit_num);
    ledcWrite(ch, period);
  } else if (last_hz[ch] > hz || last_bit[ch] > bit_num) {
    ledcWrite(ch, period);
    ledcSetup(ch, hz, bit_num);
    ledcWrite(ch, period);
  } else if (last_us[ch] != us && last_hz[ch] == hz && last_bit[ch] == bit_num) {
    ledcWrite(ch, period);
  }
  last_hz[ch] = hz;
  last_us[ch] = us;
  last_bit[ch] = bit_num;
}
