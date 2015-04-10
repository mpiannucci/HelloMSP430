#ifndef LED_H
#define LED_H

/**
 * Initialize leds
 */
void led_init(void);

/**
 * Invert the state of the red led.
 */
void led_toggle_red_state(void);

/**
 * Set the state of the red led
 * @param state 0 for off, 1 for on.
 */
void led_set_red_state(int state);

/**
 * Get the state of the red led
 * @param state 0 for off, Non zero for on.
 */
int led_get_red_state(void);

/**
 * Invert the state of the green led.
 */
void led_toggle_green_state(void);

/**
 * Set the state of the green led
 * @param state 0 for off, 1 for on.
 */
void led_set_green_state(int state);

/**
 * Get the state of the green led
 * @return state 0 for off, Non zero for on
 */
int led_get_green_state(void);

/**
 * Turn off all leds
 */
void led_all_off(void);


#endif // LED_H