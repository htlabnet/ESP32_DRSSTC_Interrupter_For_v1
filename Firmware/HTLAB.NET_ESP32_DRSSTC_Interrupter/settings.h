#ifndef SETTINGS_H
#define SETTINGS_H


// ########## Interrupter Settings ##########



// ########## Settings Complete! ##########


// Pin Number (ESP32)
#define PIN_ADC1_CS 2
#define PIN_ADC2_CS 4
#define PIN_EXP1_CS 15
#define PIN_OUT1 25
#define PIN_OUT2 26
#define PIN_OUT3 32
#define PIN_OUT4 33

// Pin Number (IO-Expander1 : LCD)
#define PIN_LCD_RS 2
#define PIN_LCD_ENA 3
#define PIN_LCD_DB4 4
#define PIN_LCD_DB5 5
#define PIN_LCD_DB6 6
#define PIN_LCD_DB7 7

// IO-Expander Register Map
#define EXP_ADDR 0x40
#define EXP_REG_DIR 0x00
#define EXP_REG_GPIO 0x09


#endif
