#include "Adxl.h"


bool Adxl::init(){
    transport->init();
    return true;
}
bool Adxl::isConnected() {
    char d;
    transport->read(0x00, &d, 1);
    return d == (char) 0xE5; // device id register
}
bool Adxl::startMeasurement() {
    char d = (char)(0x08);
    transport->write(0x2D, &d, 1); 
    return true;
}

bool Adxl::stopMeasurement() {
    char d = (char)(0x00);
    transport->write(0x2D, &d, 1);  
}
bool Adxl::readData(){
    char data[6];
    transport->read(0x32, data, 6); // data register for x-axis
    
    xValue = (short)((data[1] << 8) | (data[0] & 0XFF));
    yValue = (short)((data[3] << 8) | (data[2] & 0XFF));
    zValue = (short)((data[5] << 8) | (data[4] & 0XFF));

    return true;
}

short Adxl::getX() {
    if (lastReadAxis != 'X') {
        readData();
        lastReadAxis = 'X';
    }
    return xValue;
}
short Adxl::getY() {
    if (lastReadAxis != 'Y') {
        readData();
        lastReadAxis = 'Y';
    }
    return yValue;
}
short Adxl::getZ() {
    if (lastReadAxis != 'Z') {
        readData();
        lastReadAxis = 'Z';
    }
    return zValue;
}
