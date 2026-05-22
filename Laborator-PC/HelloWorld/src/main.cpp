#include "Arduino.h"
#include "avr8-stub.h"
#include "app_api.h" // only needed with flash breakpoints

#define PD2 1<<2
#define PD3 1<<3
#define PD4 1<<4

void setup() {
    // initialize GDB stub
    debug_init();

    // put your setup code here, to run once:
    DDRD |= PD2;
    DDRD |= PD3;
    DDRD &= ~PD4;
}

void setLed1State(char PIN){
    PORTD |= PIN;
}

void setLed0State(char PIN){
    PORTD &= ~PIN;
}

char readBtnState(){
    return (PIND & PD4)==0;
}

void loop() {
    // put your main code here, to run repeatedly:
    
    if(readBtnState()){
        setLed1State(PD2);
        setLed0State(PD3);
    }
    else{
        setLed1State(PD3);
        setLed0State(PD2);
    }
    delay(500);
}
