#ifndef ADXL_TRANSPORT_SPI_H
#define ADXL_TRANSPORT_SPI_H

#include "IAdxlTransport.h"
#include "SpiMaster.h"

class AdxlTransportSPI : public IAdxlTransport {
private:
    SpiMaster spi;
    char* port;
    char mask;

public:
    AdxlTransportSPI(char* port, char mask);
    void init();
    
    bool read(int addr, char* d, int len = 1);
    bool write(int addr, const char* d, int len = 1);
};


#endif // ADXL_TRANSPORT_SPI_H