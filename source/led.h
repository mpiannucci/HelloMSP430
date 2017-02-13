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

    /**
     * Initialize the LEDs
     */
    LED();

    /**
     * Initialize the LEDs
     */
    void init();

    /**
    * Invert the state of the given led.
    * @param color The LED to toggle
    */
    void toggle(LEDColor color);

    /**
     * Set the state of the given led
     * @param  color The LED to set the state of
     * @param  state The state to set the LED to
     */
    void setState(LEDColor color, LEDState state);

    /**
     * Get the state of the given led
     * @param  color The LED to fetch the state of
     * @return       The current state of the given color LED
     */
    LEDState state(LEDColor color);

    /**
     * Set the state of all LEDs to be the same
     * @param state The state to set all of the LEDS
     */
    void setAllState(LEDState state);

private:
    static bool initialized;
};

#endif // LED_H
