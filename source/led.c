#include <msp430.h>

#include "led.h"

#define RED_LED	  BIT0
#define GREEN_LED BIT6
#define NO_LED	  0

void led_init(void) {
    // Set the direction to output for the LEDs
    P1DIR = RED_LED | GREEN_LED;

    led_all_off();
}

void led_toggle_red_state(void) {
    P1OUT ^= RED_LED;
}

void led_set_red_state(int state) {
    if (state) {
        P1OUT |= RED_LED;
    } else {
        P1OUT &= ~(RED_LED);
    }
}

int led_get_red_state(void) {
    return (int) P1OUT & RED_LED;
}

void led_toggle_green_state(void) {
    P1OUT ^= GREEN_LED;
}

void led_set_green_state(int state) {
    if (state) {
        P1OUT |= GREEN_LED;
    } else {
        P1OUT &= ~(GREEN_LED);
    }
}

int led_get_green_state(void) {
    return (int) P1OUT & GREEN_LED;
}

void led_all_off(void) {
    P1OUT = NO_LED;
}