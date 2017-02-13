#include <msp430.h>

#include "led.h"

bool LED::initialized = false;

LED::LED() {
}

void LED::init() {
    if (initialized) {
        return;
    }

    // Set the direction to output for the LEDs
    P1DIR = RED | GREEN;

    setAllState(OFF);

    initialized = true;
}

void LED::toggle(LEDColor color) {
    P1OUT ^= color;
}

void LED::setState(LEDColor color, LEDState state) {
    switch (state) {
    default:
    case ON:
        P1OUT |= color;
        break;
    case OFF:
        P1OUT &= ~(color);
        break;
    }
}

LED::LEDState LED::state(LEDColor color) {
    return (LEDState) (P1OUT & color);
}

void LED::setAllState(LEDState state) {
    switch(state) {
    case ON:
        P1OUT |= GREEN | RED;
        break;
    case OFF:
        P1OUT = NONE;
        break;
    default:
        break;
    }
}