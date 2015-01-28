#include "led.h"


void LED::init() {
    // P1.0 and P1.6 are the red+green LEDs
    P1DIR = RED_LED + GREEN_LED;

    // All LEDs off
    P1OUT = RED_LED + GREEN_LED;
}

void LED::toggleGreenLED() {
    P1OUT ^= GREEN_LED;
}

void LED::toggleRedLED() {
    P1OUT ^= RED_LED;
}

void LED::setGreenLED(bool on) {
    // TODO
}

void LED::setRedLED(bool on) {
    // TODO
}