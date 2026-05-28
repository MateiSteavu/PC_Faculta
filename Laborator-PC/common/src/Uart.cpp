#include <Uart.h>
#include <string.h>
#include <Arduino.h>
#include <avr8-stub.h>


#define FOSC 16e6 // Clock Speed
#define BAUD 9600
#define br (FOSC/16/BAUD-1)

void Uart::init() {

    //datasheet https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf
    //frame format pag 147

    /*Set baud rate */
    // Enable receiver and transmitter */
    UCSR0B = (1<<RXEN0)|(1<<TXEN0); //pag 160

    // TODO: 1. configure UART
    // set UART pin directions
    UCSR0C = (3<<UCSZ00); //frame size, 8 bit

    // set baud rate 9600
    // enable RX and TX
    UBRR0H = 0;             //formula pagina 146
    UBRR0L = 103;
    // set frame format: 8 bits, 1 stop bit, no parity
    // DO NOT CHANGE ALL BITS
}

void Uart::writeByte(const char& d) {
    // TODO: 2. implement write + test it and capture on oscilloscope
    // wait to empty transmit buffer
    // write data
    while (!(UCSR0A & (1<<UDRE0)))  //pag 156
    ;
    UDR0 = d;
}

bool Uart::available() {
    if(UCSR0A & (1 << RXC0)) // data available
        return true;
    // TODO: 3. check if are data in UART buffer
    return false;
}

char Uart::readByte() {
    // TODO: 3. implement read
    // wait for data
    while (!(UCSR0A & (1<<RXC0)))
    ;
     return UDR0;
    // read data and return it
}

void Uart::writeString(const char* msg) {
    for (int i = 0; i < strlen(msg); i++)
        writeByte(msg[i]);
}
char B[16];
void Uart::writeIntegerNumber(const int &number, const int &base) {
    itoa(number, B, base);
    writeString(B);
}
