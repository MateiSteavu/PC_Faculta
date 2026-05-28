#include "I2CTransport.h"


// TODO: 1. based on IAdxlTransport interface implement two other classes
void I2cTransport::init(){
    i2c.init();
}

bool I2cTransport::write(int addr, const char* d, int len = 1){
    for(short i = 0; i<len;i++){
        i2c.sendStart();
        i2c.writeAddrWrite(dev_addr);
        i2c.writeByte(addr, ACKNOWLEDGE);
        i2c.writeByte(d[i], ACKNOWLEDGE);
        i2c.sendStop();
    }
    return true;
}

bool I2cTransport::read(int addr, char* d, int len = 1){
    for(short i = 0; i<len;i++){
        i2c.sendStart();
        i2c.writeAddrWrite(dev_addr);
        i2c.writeByte(addr, ACKNOWLEDGE );
        i2c.sendStart();
        i2c.writeAddrRead(dev_addr);
        i2c.readByte(d[i], NOT_ACKNOWLEDGE);
        i2c.sendStop();
    }
    return true;
}