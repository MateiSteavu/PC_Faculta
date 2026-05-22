// 1. implement an OSI model for ADXL345 with I2C and SPI

#include "Arduino.h"
#include "avr8-stub.h"
#include "app_api.h"
#include "Uart.h"
#include "I2cMaster.h"
#include "SpiMaster.h"
#include "IAdxlTransport.h"
#include "I2CTransport.h"
#include "Adxl.h"

Uart uart;


// // - one SpiTransport for SPI protocol
// class SpiTransport : public IAdxlTransport {
//     SpiMaster spi;
// public:
//     SpiTransport() {
//         spi.init();
//     }

//     void writeRegister(char reg, char data) override {
//         PORTB &= ~(1 << PORTB2); // CS low
//         spi.transmit(reg);
//         spi.transmit(data);
//         PORTB |= (1 << PORTB2); // CS high
//     }
//     char readRegister(char reg) override {
//         PORTB &= ~(1 << PORTB2); // CS low
//         spi.transmit(reg | 0x80); // set read bit
//         char data = spi.transmit(0xFF);
//         PORTB |= (1 << PORTB2); // CS high
//         return data;
//     }
// };

// TODO: 2. implement Adxl high level class
// class Adxl {
//     IAdxlTransport* transport; 
//     int16_t x, y, z;
//     char lastReadAxis;
// public:
//     Adxl(IAdxlTransport * t) : transport(t), x(0), y(0), z(0), lastReadAxis(0) {}
    
//     void init(){

//     }

//     bool isConnected() {
//         char d;
//         transport->read(0x00, &d, 1);
//         uart.writeIntegerNumber(d, 16);
//         return d == (char) 0xE5; // device id register
//     }
//     void startMeasurement() {
//         char d = (char)(0x08);
//         transport->write(0x2D, &d, 1); 
//     }
//     void stopMeasurement() {
//         char d = (char)(0x00);
//         transport->write(0x2D, &d, 1);  
//     }
//     void readData(){
//         char data[6];
//         transport->read(0x32, data, 6); // data register for x-axis
        
//         x = (int16_t)((data[1] << 8) | (data[0] & 0XFF));
//         y = (int16_t)((data[3] << 8) | (data[2] & 0XFF));
//         z = (int16_t)((data[5] << 8) | (data[4] & 0XFF));
//     }
    
//     int16_t getX() {
//         if (lastReadAxis != 'X') {
//             readData();
//             lastReadAxis = 'X';
//         }
//         return x;
//     }
//     int16_t getY() {
//         if (lastReadAxis != 'Y') {
//             readData();
//             lastReadAxis = 'Y';
//         }
//         return y;
//     }
//     int16_t getZ() {
//         if (lastReadAxis != 'Z') {
//             readData();
//             lastReadAxis = 'Z';
//         }
//         return z;
//     }
// };

Adxl* adxl;

// TODO: 3. TEST IT!
void setup() {
    // initialize GDB stub
    //debug_init();
    uart.init();
    
    adxl = new Adxl(new I2cTransport());
    adxl->init();
    if (adxl->isConnected()) {
        uart.writeString("s-o conectat bAAAAAAAAAAA");
        adxl->startMeasurement();
    }
    else {
        uart.writeString("Nema");
    }
}

void loop() {
    if (adxl->isConnected()) {
       adxl->readData();
       uart.writeString("X: ");
       uart.writeIntegerNumber(adxl->getX(), 10);
       uart.writeString("Y: ");
       uart.writeIntegerNumber(adxl->getY(), 10);
       uart.writeString("Z: ");
       uart.writeIntegerNumber(adxl->getZ(), 10);
       uart.writeString("\r\n");
       delay(500);
    }
}