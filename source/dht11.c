#include "dht11.h"
#include "timer.h"
#include <msp430.h>

#define DHT_DATA_PIN BIT4

/**
 * Latest data read from the device
 */
DHT11_Data data;

volatile unsigned char timeout;

void dht11_init() {
    // Set up the timer
    timer_a_init();

    // Set the timer interrupt callback
    timer_a_set_isr(dht11_isr_callback);
}

void dht11_send_start_signal(void) {
    // Set the pin to output mode
    P2DIR |= DHT_DATA_PIN;

    // Set the pin low
    P2OUT &= (~DHT_DATA_PIN);

    // Delay for 18ms
    __delay_cycles(25000);

    // Set the pin high
    P2OUT |= DHT_DATA_PIN;

    // Delay for 20-40ms
    __delay_cycles(35);

    // Set the direction to input mode to prepare for the response
    P2DIR &= (~DHT_DATA_PIN);
}

unsigned int dht11_check_response(void) {
    // Reset the timeout flag
    timeout = 0;

    // Reset the timer, change capture value, and enable the interrupt
    timer_a_reset();
    timer_a_set_count(25);
    timer_a_start(UP);
    timer_a_enable_isr(1);

    // Wait for the signal to go low and make sure the timer hasnt expired
    while ( !(P2IN & DHT_DATA_PIN) && !timeout );

    if (timeout) {
        // If the timer has expired again
        return 0;
    }

    // Clear the timer again, and enable interrupts
    timer_a_reset();
    timer_a_enable_isr(1);

    // wait for the data pin to go high and make sure the timer hasnt expired
    while( (P2IN & DHT_DATA_PIN) && !timeout );

    if (timeout) {
        // If the timer overflowed, return failure
        return 0;
    } else {
        // Disable interrupts and return successful
        timer_a_enable_isr(0);
        return 1;
    }
}

unsigned char dht11_read_byte(void) {
    // Reset the timeout flag
    timeout = 0;

    // Initilaize the byte value and the counter value
    unsigned char received_value = 0;
    unsigned char bit = 0;

    // Switch off interrupts
    timer_a_enable_isr(0);

    for (bit = 8; bit > 0; bit--) {
        // Wait for the pin to go high
        while( !(P2IN & DHT_DATA_PIN) );

        // Set up and start the timer
        timer_a_reset();
        timer_a_start(UP);
        timer_a_enable_isr(1);

        // Wait for the pin to go low again
        while( P2IN & DHT_DATA_PIN );

        // Stop the timer count
        timer_a_stop();

        // Check the timer count, if enough time passed,
        // the bit was a one so write it
        if (timer_a_count() > 13) {
            received_value |= 1 << (bit - 1);
        }
    }

    return received_value;
}

unsigned int dht11_verify_checksum() {
    if (data.CheckSum == (data.Humidity + data.Temperature + data._humidity + data._temperature)) {
        return 1;
    } else {
        return 0;
    }
}

DHT11_Data dht11_get_data(void) {
    dht11_send_start_signal();
    if (dht11_check_response()) {
        data.Humidity = dht11_read_byte();
        data._humidity = dht11_read_byte();
        data.Temperature = dht11_read_byte();
        data._temperature = dht11_read_byte();
        data.CheckSum = dht11_read_byte();
    }

    // Clear timer, set timer to up mode, and reset the timer overflow
    timer_a_reset();
    timer_a_start(UP);
    timer_a_set_count(50000);

    return data;
}

void dht11_isr_callback(void) {
    timeout = 1;
    timer_a_clear_isr_flag();
}