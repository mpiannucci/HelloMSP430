/**
 * led.h
 *
 * Module for controlling the LEDs onboard the Launchpad Develepment Board.
 *
 * @author Matthew Iannucci, 2015
 */

#ifndef LED_H
#define LED_H

class LED {

public:
    enum LEDColor {
        NONE = 0,
        RED = BIT0,
        GREEN = BIT6
    };

    enum LEDState {
        ON = 1,
        OFF = 0
    };

    LED();
    void toggle(LEDColor color);
    void setState(LEDColor color, LEDState state);
    LEDState state(LEDColor color);
    void setAllState(LEDState state);
};

#endif // LED_H
