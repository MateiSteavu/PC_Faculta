#include <SpiMaster.h>
#include "avr8-stub.h"
#include <Uart.h>

void SpiMaster::init() {
    // TODO: 1. configure SPI
    /* ---!VERY IMPORTANT!--- */
    // write 1 on CS after set CS as OUTPUT

    // in the end configure SPI
    // set MOSI, SCK - output
    // set MISO - input
    DDRB |= (1 << PB2); //NU SUNT MASTI
    PORTB |= (1 << PB2);
    // DDRD = PD2;
    // PORTD = PD2;
    
    DDRB |= (1<<PB5);
    DDRB |= (1<<PB3);
    
    DDRB &= ~(1<<PB4);

    // enable SPI as master
    SPCR = (1<<SPR0) | (1<<CPHA) | (1<<CPOL) | (1<<SPE) | (1<<MSTR);

    // check ADXL datasheet for clock frequency
    // check ADXL datasheet for clock polarity
    // check ADXL datasheet for clock phase
}

char SpiMaster::transmit(const char& d) {
    // TODO: 2. transmit 1 byte on SPI
    /* Start transmission */
    SPDR = d;
    /* Wait for transmission complete */
    while(!(SPSR & (1<<SPIF)));
    //uart.writeByte('a');
    /* Return Data Register */
    return SPDR;
}