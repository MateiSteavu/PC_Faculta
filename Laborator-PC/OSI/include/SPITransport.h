#ifndef ADXL_TRANSPORT_SPI_H
#define ADXL_TRANSPORT_SPI_H

#include "IAdxlTransport.h"
#include "SpiMaster.h"
#include "avr8-stub.h"

class SpiTransport : public IAdxlTransport {
private:
    SpiMaster spi;

public:
    SpiTransport() {};
    void init();
    
    bool read(int addr, char* d, int len = 1);
    bool write(int addr, const char* d, int len = 1);
};


#endif // ADXL_TRANSPORT_SPI_H