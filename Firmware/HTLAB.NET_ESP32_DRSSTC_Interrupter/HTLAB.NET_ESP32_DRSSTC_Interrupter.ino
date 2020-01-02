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
//  IO12 - HSPI IQ [MISO] (ADC1, ADC2, LCD IOExp)
//  IO13 - HSPI ID [MOSI] (ADC1, ADC2, LCD IOExp)
//  IO14 - HSPI CLK [SCK] (ADC1, ADC2, LCD IOExp)
//  IO15 - HSPI CS [SS] (LCD IOExp CS)
//  IO16 - UART2 RXD (MIDI IN)
//  IO17 - UART2 TXD (MIDI OUT)
//  IO18 - VSPI CLK [SCK] (SD CLK)
//  IO19 - VSPI IQ [MISO] (SD DAT0) Need pull-up
//  IO21 - PIEZO SPEAKER
//  IO22 - UART0 MODE OUT (MIDI/UART)
//  IO23 - VSPI ID [MOSI] (SD CMD)
//  IO25 - DAC1 (LCD CONTRAST)
//  IO26 - OUT
//  IO27 - OUT
//  IO32 - OUT
//  IO33 - OUT
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



void setup() {

  pinMode(MISO, PULLUP);
  dacWrite(25, 200);

}



void loop() {

}
