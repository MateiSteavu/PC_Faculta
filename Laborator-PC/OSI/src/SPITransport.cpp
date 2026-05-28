#include "SPITransport.h"

// AdxlTransportSPI::AdxlTransportSPI(char* port, char mask) {
//     this->port = port;
//     this->mask = mask;
// }

void SpiTransport::init() {
     spi.init();
}

bool SpiTransport::read(int addr, char* d, int len = 1){
    PORTB &= ~(1 << PORTB2); // CS low
    spi.transmit(addr | 0x80); // set read bit
    for(int i = 0; i<len;i++)
        d[i] = spi.transmit(0xFF);
    PORTB |= (1 << PORTB2); // CS high
    return true;
}

bool SpiTransport::write(int addr, const char* d, int len = 1){
    PORTB &= ~(1 << PORTB2); // CS low
    spi.transmit(addr);
    for(int i = 0; i<len;i++)
        spi.transmit(d[i]); 
    PORTB |= (1 << PORTB2); // CS high
    return true;
}