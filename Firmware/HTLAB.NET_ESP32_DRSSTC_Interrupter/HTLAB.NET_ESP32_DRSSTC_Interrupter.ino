//
// #################################################
//
//    HTLAB.NET ESP32 DRSSTC Interrupter
//      https://htlab.net/electronics/teslacoil/
//
//    Copyright (C) 2019 - 2020
//      Hideto Kikuchi / PJ (@pcjpnet) - http://pc-jp.net/
//      Tsukuba Science Inc. - http://www.tsukuba-kagaku.co.jp/
//
//    !!!!! NOT ALLOWED COMMERCIAL USE !!!!!
//
// #################################################
//

//
// ########## Compatible Boards ##########
//    - ESP32-DevKitC
//

//
// ########## ESP32 Pin Assignments ##########
//  IO0 - NONE
//  IO2 - HSPI CS [SS] (ADC1 CS)
//  IO4 - HSPI CS [SS] (ADC2 CS)
//  IO5 - VSPI CS [SS] (SD DAT3)
//  IO12 - HSPI IQ [MISO] (ADC1, ADC2, LCD-IOExp)
//  IO13 - HSPI ID [MOSI] (ADC1, ADC2, LCD-IOExp)
//  IO14 - HSPI CLK [SCK] (ADC1, ADC2, LCD-IOExp)
//  IO15 - HSPI CS [SS] (LCD-IOExp CS)
//  IO16 - UART2 RXD (MIDI IN)
//  IO17 - UART2 TXD (MIDI OUT)
//  IO18 - VSPI CLK [SCK] (SD CLK)
//  IO19 - VSPI IQ [MISO] (SD DAT0) Need pull-up
//  IO21 - PIEZO SPEAKER
//  IO22 - UART0 MODE OUT (MIDI/UART)
//  IO23 - VSPI ID [MOSI] (SD CMD)
//  IO25 - OUT1
//  IO26 - OUT2
//  IO27 - NONE
//  IO32 - OUT3
//  IO33 - OUT4
//  IO34 - Internal ADC1 CH6 (BATT VOLTAGE)
//  IO35 - NONE
//

//
// ########## Require Libraries ##########
//    - MIDI Library 4.3
//

//
// ########## MCP23S08 Pin Assignments ##########
//  GP0 - NONE
//  GP1 - NONE
//  GP2 - LCD RS
//  GP3 - LCD ENA
//  GP4 - LCD DB4
//  GP5 - LCD DB5
//  GP6 - LCD DB6
//  GP7 - LCD DB7

// SPI
#include <SPI.h>
SPIClass hSPI(HSPI);

// Settings
#include "settings.h"

// Pin I/O
#include "lib_input.h"
#include "lib_output.h"


void setup() {

  pinMode(MISO, PULLUP);
  Serial.begin(115200);

  pinMode(PIN_OUT1, OUTPUT);
  pinMode(PIN_OUT2, OUTPUT);
  pinMode(PIN_OUT3, OUTPUT);
  pinMode(PIN_OUT4, OUTPUT);

  //ledcSetup(0, 10, 18);
  //ledcAttachPin(PIN_OUT1, 0);
  //ledcWrite(0, 1);

  // HSPI Initialize
  pinMode(PIN_ADC1_CS, OUTPUT);
  pinMode(PIN_ADC2_CS, OUTPUT);
  pinMode(PIN_EXP1_CS, OUTPUT);
  digitalWrite(PIN_ADC1_CS, HIGH);
  digitalWrite(PIN_ADC2_CS, HIGH);
  digitalWrite(PIN_EXP1_CS, HIGH);
  hSPI.begin();

  // IO Expander Initialize
  expInit(hSPI, PIN_EXP1_CS);


  // LCD Custom Character
  spiLcdBegin(hSPI, PIN_EXP1_CS, PIN_LCD_RS, PIN_LCD_ENA, PIN_LCD_DB4, PIN_LCD_DB5, PIN_LCD_DB6, PIN_LCD_DB7);
  byte lcd_play[8] = {B01000,B01100,B01110,B01111,B01110,B01100,B01000};
  byte lcd_stop[8] = {B00000,B11111,B11111,B11111,B11111,B11111,B00000};
  byte lcd_down[8] = {B00000,B00000,B00000,B10001,B01010,B00100,B00000};
  spiLcdCreateChar(0, lcd_stop);
  spiLcdCreateChar(1, lcd_play);
  spiLcdCreateChar(2, lcd_down);

  // LCD Initialize (IO Expander 1)
  spiLcdBegin(hSPI, PIN_EXP1_CS, PIN_LCD_RS, PIN_LCD_ENA, PIN_LCD_DB4, PIN_LCD_DB5, PIN_LCD_DB6, PIN_LCD_DB7);

  spiLcdSetCursor(8,0);
  spiLcdCustomChar(0);
  spiLcdCustomChar(1);
  spiLcdCustomChar(2);
  delay(2000);

}


void loop() {

  spiLcdClear();
  spiLcdSetCursor(0,2);
  
  for (uint8_t ch = 0 ; ch <8 ; ch++ ) {
    uint16_t adc = adcRead(hSPI, PIN_ADC1_CS, ch);
    Serial.println("CH" + String(ch) +": " + String(adc)) ;
  }
  Serial.println("----------------------------------------") ;
  //expPinWrite(hSPI, PIN_EXP1_CS, 0, HIGH);
  delay(500);
  //expPinWrite(hSPI, PIN_EXP1_CS, 1, HIGH);
  delay(500);
  //expPinWrite(hSPI, PIN_EXP1_CS, 0, LOW);
  delay(500);
  //expPinWrite(hSPI, PIN_EXP1_CS, 1, LOW);
  delay(500);

  spiLcdPrint("TEST");
  delay(2000);
}


void IRAM_ATTR isr_ms_timer() {
  //Serial.println("ms");
}
