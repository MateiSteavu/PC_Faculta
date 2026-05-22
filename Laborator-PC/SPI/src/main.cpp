// Objectives:
// 1. configure SPI
// 2. comupaction over SPI
// 3. ADXL345 usage

// Components
// ADXL345 module
// Bidirectional level shifter

// Docs
// ADXL345 Datasheet: https://www.analog.com/media/en/technical-documentation/data-sheets/adxl345.pdf


// HINTS
// use UART lib from lab2 to send messages to PC
// use itoa to convert int to string

#include "Arduino.h"
#include "avr8-stub.h"
#include "app_api.h" // only needed with flash breakpoints
#include <SpiMaster.h>
#include <Uart.h>

SpiMaster spi;
Uart uart;

void ADXL_enable() {
    PORTB &= ~(1<<PB0);
    // TODO: 2. select ADXL
}

void ADXL_disable() {
    PORTB |= (1<<PB0);
    // TODO: 2. deselect ADXL
}

char ADXL_cmdBuilder(char addr, bool rw, bool mb) {
    return (addr & 0b00111111) | (mb << 6) | (rw << 7);
}

char rec;

void setup() {
    // initialize GDB stub
    //debug_init();

    // TODO: 1. set an CS pin and make it as output
    DDRB |= (1 << PB0);
    uart.init();
    
    ADXL_disable();

    spi.init();

    // TODO: 2. read ADXL DEVICE ID
    ADXL_enable();
    spi.transmit(0x80);
    // analyze SPI protocol on oscilloscope
    // expected response 0xE5
    rec = spi.transmit(0x00);
    ADXL_disable();
    uart.writeIntegerNumber(rec, 16);
    delay(500);

    // TODO: 3. enable ADXL read mode
    
    delay(500);
    ADXL_enable();
    spi.transmit(0x2D);
    spi.transmit(1<<3);
    ADXL_disable();
}

char X_MSB, X_LSB,Y_MSB, Y_LSB,Z_MSB, Z_LSB;

int X, Y, Z;

void ADXL_readData() {
    ADXL_enable();
    // TODO: 3. read X, Y, Z from ADXL and send to PC

    spi.transmit(0xF2);
    X_LSB = spi.transmit(0x00);
    X_MSB = spi.transmit(0x00);
    Y_LSB = spi.transmit(0x00);
    Y_MSB = spi.transmit(0x00);
    Z_LSB = spi.transmit(0x00);
    Z_MSB = spi.transmit(0x00);
    ADXL_disable();
    X = (int)((X_MSB << 8) | X_LSB);
    Y = (int)((Y_MSB << 8) | Y_LSB);
    Z = (int)((Z_MSB << 8) | Z_LSB);
    uart.writeString("DATA X ESTE \n:");
    uart.writeIntegerNumber(X, 10);
    uart.writeString("\nDATA Y ESTE \n:");
    uart.writeIntegerNumber(Y, 10);
    uart.writeString("\nDATA Z ESTE \n:");
    uart.writeIntegerNumber(Z, 10);
    uart.writeString("\n");
}

void loop() {
    ADXL_readData();
    delay(500);
}