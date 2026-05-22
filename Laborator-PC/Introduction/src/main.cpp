// Objectives:
// 1. presenting ATmega32p datasheet
// 2. pin configuration for in/out
// 3. read/write from pins
// 4. introduction in electrical workbench equipments
//  4.1. presentation + utilization multimeter (measure R, Vd)
//  4.2. presentation + visualization on oscilloscope
//  4.3. presentation programmable power supply

// Components
// 2 LEDs + resistors
// 1 Push Button + resistor


#include "Arduino.h"
#include "avr8-stub.h"
#include "app_api.h" // only needed with flash breakpoints
#include "../include/laboratory_types.h"


#define PD2 (1<<2)
#define PD3 (1<<3)
#define PD4 (1<<4)

void setup() {
    // initialize GDB stub
    debug_init();

    // TODO: 1. configure pin directions and turn off leds
    DDRD |= PD2;
    DDRD |= PD3;
    DDRD &= ~PD4;

    PORTD &= ~PD2;
    PORTD &= ~PD3;
}

void inline setLed0State(LedState state) {
    if(state == ON){
        PORTD |= PD2;
    }
    else{
        PORTD &= ~PD2;
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
        PORTD |= PD3;
    }
    else{
        PORTD &= ~PD3;
    }
}

static void oscillatingLed() {
    static int i=0   ;
    i++;
    if(i==5)
        setLed1State(LedState::ON);
    if(i==7)
        setLed1State(LedState::OFF);
    if(i==7)
        i=0;
    // TODO: 2. toggle the led1 with the pattern: 500ms on, 200ms off
    // TODO: 3. analyze on oscliisop the  led1 signal and measure the timing
}

// detect button press and toggle the led0 state
static void toggleLed(ButtonState btnState) {
    static bool lastState = ButtonState::NOT_PRESSED;
    static bool ledState = false;
    if ( lastState == ButtonState::NOT_PRESSED && 
            btnState == ButtonState::PRESSED ) {
        ledState = !ledState;
        setLed0State(ledState ? LedState::ON : LedState::OFF);
    }
    lastState = btnState;
}

void loop() {
    toggleLed(readBtnState());
    oscillatingLed();
    delay(100);
}