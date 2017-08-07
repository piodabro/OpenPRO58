#ifndef HW_CONFIG_H
#define HW_CONFIG_H

// Buttons on module (required)
#define PIN_BUTTON_UP           PA8
#define PIN_BUTTON_MODE         PB14
#define PIN_BUTTON_DOWN         PB12

// Inputs on module (optional inputs from headset)
#define PIN_BUTTON_EB0          PB13
#define PIN_BUTTON_EB1          PA11
#define PIN_BUTTON_EB2          PB15

#define PIN_BUZZER              PB8

// Receiver module A
#define PIN_RSSI_A              PA0
#define PIN_LED_A               PB9

// Receiver module B
#ifdef USE_DIVERSITY
    #define PIN_LED_B           PA2
    #define PIN_RSSI_B          PA1
#endif

// Receiver switch
#define PIN_SW                  PC15

#define PIN_SPI_DATA            PA5
#define PIN_SPI_SLAVE_SELECT_A  PA4
#define PIN_SPI_SLAVE_SELECT_B  PA3
#define PIN_SPI_CLOCK           PA7

#endif // file_defined
