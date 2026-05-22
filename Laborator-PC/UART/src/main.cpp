// Objectives:
// 1. configure UART on ATmega328p
// 2. write bytes on UART
// 3. receive bytes on UART
// 4. text protocols

// Components
// 2 LEDs + resistors
// 1 Push Button + resistor

#include "Arduino.h"
#include <Uart.h>
#include "../include/laboratory_types.h"

#define P9 (1<<1)
#define PD3 (1<<3)
#define PD4 (1<<4)

#define TOP (uint16_t)(700e-3*16e6/1024)
#define Valoare (uint16_t)(500e-3*16e6/1024)

Uart uart;

void setup() {
    // initialize GDB stub
    DDRB |= P9;
    DDRD |= PD3;
    DDRD &= ~PD4;

    PORTB &= ~P9;
    PORTD &= ~PD3;
    uart.init();
}

void inline setLed0State(LedState state) {
    if(state == ON){
        PORTD |= PD3;
    }
    else{
        PORTD &= ~PD3;
    }
}

// read button state
ButtonState inline readBtnState() {
    ButtonState b1;
    if((PIND & PD4)>>4==1)
        b1 = ButtonState::PRESSED;
    else
        b1 = ButtonState::NOT_PRESSED;
    return b1; 
}

void inline setLed1State(LedState state) {
    if(state == ON){
        PORTB |= P9;
    }
    else{
        PORTB &= ~P9;
    }
}

// static void oscillatingLed() {
//     static int i=0   ;
//     i++;
//     if(i==5)
//         setLed1State(LedState::ON);
//     if(i==7)
//         setLed1State(LedState::OFF);
//     if(i==7)
//         i=0;
//     // TODO: 2. toggle the led1 with the pattern: 500ms on, 200ms off
//     // TODO: 3. analyze on oscliisop the  led1 signal and measure the timing
// }

void responseBack(const char* userMsg) {
    uart.writeString("You said: ");
    uart.writeString(userMsg);
}

char c;
char buf[100];
short i = 0;
unsigned int j;

bool ledState = false;

void loop() {
    // TODO: 3. buffer bytes from user and when reach newline(\n) send the buffer back - use responseBack(...)
     
    if(uart.available()){
        c = uart.readByte();

        if(c=='\n'){
            buf[i++]='\n';
            buf[i]='\0';
            responseBack(buf);
            i=0;
        }
        else{        
            if(c == ';'){
                if(readBtnState() == ButtonState::PRESSED)
                    uart.writeString("E apasat butonu\n");
                else
                    uart.writeString("Nu e apasat butonu\n");
            }
            else{
                if(c == '0'){
                    ledState = !ledState;
                    setLed0State(ledState ? LedState::ON : LedState::OFF);
                }
                else{
                    if(c=='_'){
                        TCCR1A = (0b10<<0)|(0b11<<6);  
                        TCCR1B = (0b11<<3)|(0b101<<0);
                        ICR1 = TOP;
                        OCR1A = Valoare;
                    }
                    else{
                        if(c=='-'){
                            TCCR1A = 0;  
                            TCCR1B = 0;
                            ICR1 = 0;
                            OCR1A = 0;
                        }
                        else
                            buf[i++] = c;
                    }
                }
            }
        }
    }


    // TODO: 4. implement a text protocol with the following minimal features:
    //  - one button to read state (pressed or not)
    //  - one led to set state (on or off)
    //  - one blinking led (500ms on, 200ms off) and enable or disable it
    // DO NOT BLOCK THE MCU
    // HINT: standalone timer, internal timer, multiple options
}