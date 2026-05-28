// // Objectives:
// // 1. implement an OSI model for ADXL345 with I2C and SPI

#include "Arduino.h"
#include "avr8-stub.h"
#include "app_api.h"
#include "Uart.h"
#include "I2cMaster.h"
#include "SpiMaster.h"
#include "IAdxlTransport.h"


// TODO: 1. based on IAdxlTransport interface implement two other classes
class I2cTransport : public IAdxlTransport {
    I2cMaster i2c;
    const char dev_addr = 0x53; // ADXL345 I2C address
public:
    I2cTransport() {}

    void init();

    bool write(int addr, const char* d, int len = 1);
    bool read(int addr, char* d, int len = 1);
}; 