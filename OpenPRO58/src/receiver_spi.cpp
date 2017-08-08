#include <Arduino.h>
#include <stdint.h>

#include "receiver_spi.h"
#include "settings.h"
#include "hw_config.h"

#include <SPI.h>

// static inline void sendBit(uint8_t value);
// static inline void sendBits(uint32_t bits, uint8_t count = 20);
static void initSPI();
static void sendSlaveSelect(uint8_t value);
static void sendRegister(uint8_t address, uint32_t data);
static bool spiInitialized = false;

#define SPI_ADDRESS_SYNTH_A 0x01
#define SPI_ADDRESS_POWER 0x0A


namespace ReceiverSpi {
    //
    // Sends SPI command to receiver module to change frequency.
    //
    // Format is LSB first, with the following bits in order:
    //     4 bits - address
    //     1 bit  - read/write enable
    //    20 bits - data
    //
    // Address for frequency select (Synth Register B) is 0x1
    // Expected data is (LSB):
    //     7 bits - A counter divider ratio
    //      1 bit - seperator
    //    12 bits - N counter divder ratio
    //
    // Forumla for calculating N and A is:/
    //    F_lo = 2 * (N * 32 + A) * (F_osc / R)
    //    where:
    //        F_osc = 8 Mhz
    //        R = 8
    //
    // Refer to RTC6715 datasheet for further details.
    //
    void setSynthRegisterB(uint16_t value) {
        if(!spiInitialized)
            initSPI();
        
        sendRegister(SPI_ADDRESS_SYNTH_A, value);
    }

    void setPowerDownRegister(uint32_t value) {
        if(!spiInitialized)
                    initSPI();

        sendRegister(SPI_ADDRESS_POWER, value);
    }
}

static void initSPI(){
    SPI.begin(); //Default SPI port of STM32F103 is SPI_1.
    SPI.setBitOrder(LSBFIRST); //5808 uses LSBFirst order
    SPI.setDataMode(SPI_MODE0);
    SPI.setClockDivider(SPI_CLOCK_DIV64); //for ~1MHz 72 / 64 = 1,125MHz
    SPI.setDataSize(DATA_SIZE_16BIT); //for 16bit frame length
    spiInitialized = true;
}

static void sendRegister(uint8_t address, uint32_t data) {
    sendSlaveSelect(LOW);

    uint16_t first16bit = (data & 0x7FF) << 5; //first 11 bits of data
    first16bit |= 1 << 4; //write bit
    first16bit |= address; //address

    //sendBits(address, 4);
    //sendBit(HIGH); // Enable write.

    SPI.transfer16(first16bit);
    SPI.transfer16((data >> 11) & 0x1FF); //last 9 data bits;

    //sendBits(data, 20);

    // Finished clocking data in
    sendSlaveSelect(HIGH);
    //digitalWrite(PIN_SPI_CLOCK, LOW);
    //digitalWrite(PIN_SPI_DATA, LOW);
}


// static inline void sendBits(uint32_t bits, uint8_t count) {
//     for (uint8_t i = 0; i < count; i++) {
//         sendBit(bits & 0x1);
//         bits >>= 1;
//     }
// }

// static inline void sendBit(uint8_t value) {
//    digitalWrite(PIN_SPI_CLOCK, LOW);
//     delayMicroseconds(1);

//     digitalWrite(PIN_SPI_DATA, value);
//     delayMicroseconds(1);
//     digitalWrite(PIN_SPI_CLOCK, HIGH);
//     delayMicroseconds(1);

//     digitalWrite(PIN_SPI_CLOCK, LOW);
//     delayMicroseconds(1);
// }

static void sendSlaveSelect(uint8_t value) {
    digitalWrite(PIN_SPI_SLAVE_SELECT_A, value);
    digitalWrite(PIN_SPI_SLAVE_SELECT_B, value);
    delayMicroseconds(1);
}
