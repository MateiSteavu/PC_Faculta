// 1. implement an OSI model for ADXL345 with I2C and SPI

#include "Arduino.h"
#include "avr8-stub.h"
#include "app_api.h"
#include "Uart.h"
#include "I2cMaster.h"
#include "SpiMaster.h"
#include "IAdxlTransport.h"
#include "I2CTransport.h"
#include "SPITransport.h"
#include "Adxl.h"

Uart uart;




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