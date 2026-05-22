// // // Objectives:
// // // 1. implement an OSI model for ADXL345 with I2C and SPI

// #include "Arduino.h"
// #include "avr8-stub.h"
// #include "app_api.h"
// #include "Uart.h"
// #include "I2cMaster.h"
// #include "SpiMaster.h"
// #include "IAdxlTransport.h"


// // TODO: 1. based on IAdxlTransport interface implement two other classes
// class I2cTransport : public IAdxlTransport {
//     I2cMaster i2c;
//     const char dev_addr = 0x53; // ADXL345 I2C address
// public:
//     I2cTransport() {}

//     void init(){
//         i2c.init();
//     }

//     bool write(int addr, const char* d, int len = 1){
//         for(short i = 0; i<len;i++){
//             i2c.sendStart();
//             i2c.writeAddrWrite(dev_addr);
//             i2c.writeByte(addr, ACKNOWLEDGE);
//             i2c.writeByte(d[i], ACKNOWLEDGE);
//             i2c.sendStop();
//         }
//         return true;
//     }
//     bool read(int addr, char* d, int len = 1){
//         for(short i = 0; i<len;i++){
//             i2c.sendStart();
//             i2c.writeAddrWrite(dev_addr);
//             i2c.writeByte(addr, ACKNOWLEDGE );
//             i2c.sendStart();
//             i2c.writeAddrRead(dev_addr);
//             i2c.readByte(d[i], NOT_ACKNOWLEDGE);
//             i2c.sendStop();
//         }
//         return true;
//     }
// }; 