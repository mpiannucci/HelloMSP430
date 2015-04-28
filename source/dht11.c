#include "dht11.h"
#include "timer.h"
#include <msp430.h>

#define DHT_DATA_PIN BIT4

/**
 * Latest data read from the device
 */
DHT11_Data data;

void dht11_init() {
    // Set up the timer
    timer_a_init();
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
    // TODO: Recieve the response to the start signal

    return 1;
}

unsigned char dht11_read_byte(void) {
    // TODO: Receive the pending byte from the device

    return 1;
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
    return data;
}