// #include "AdxlTransportSPI.h"

// AdxlTransportSPI::AdxlTransportSPI(char* port, char mask) {
//     this->port = port;
//     this->mask = mask;
// }

// void AdxlTransportSPI::init() {
//     spi.init();
//     // Configure chip select pin as output
//     *port |= mask;  // Set to high (inactive)
// }

// bool AdxlTransportSPI::read(int addr, char* d, int len = 1) {
//     // SPI read: set bit 7 to 1, bit 6 to 1 for multi-byte read
//     char command = (0x80 | (len > 1 ? 0x40 : 0x00) | addr);
    
//     *port &= ~mask;  // Chip select low
    
//     spi.transmit(command);
//     for (int i = 0; i < len; i++) {
//         d[i] = spi.transmit(0x00);
//     }
    
//     *port |= mask;  // Chip select high
//     return true;
// }

// bool AdxlTransportSPI::write(int addr, const char* d, int len = 1) {
//     // SPI write: bit 7 = 0 for write, bit 6 = 1 for multi-byte write
//     char command = ((len > 1 ? 0x40 : 0x00) | addr);
    
//     *port &= ~mask;  // Chip select low
    
//     spi.transmit(command);
//     for (int i = 0; i < len; i++) {
//         spi.transmit(d[i]);
//     }
    
//     *port |= mask;  // Chip select high
//     return true;
// }