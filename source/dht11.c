#include "dht11.h"
#include "timer.h"
#include "uart.h"
#include <msp430.h>

#define DHT_DATA_PIN BIT4

/**
 * Latest data read from the device
 */
DHT11_Data data;

unsigned int start_time, end_time;

void dht11_init() {
    data.Humidity = 0;
    data._humidity = 0;
    data.Temperature = 0;
    data._temperature = 0;
    data.CheckSum = 0;

    // Set up the timer
    timer_a_init();
    timer_a_start(UP_CONTINUOUS);
}

void dht11_send_start_signal(void) {
    // Set the pin low
    P1OUT &= ~(DHT_DATA_PIN);

    // Set the pin to output mode
    P1DIR |= DHT_DATA_PIN;

    // Drive the pull up low
    P1REN &= ~(DHT_DATA_PIN);

    // Delay for 18ms
    start_time = timer_a_count();
    while ((timer_a_count() - start_time) < 18000);

    // Set the pin high
    P1REN |= DHT_DATA_PIN;
    P1OUT |= DHT_DATA_PIN;

    // Set the direction to input mode to prepare for the response
    P1DIR &= ~(DHT_DATA_PIN);
}

unsigned int dht11_check_response(void) {
    // Wait for the signal to go high or for the timer to expire
    while ( P1IN & DHT_DATA_PIN ) {
        if ((timer_a_count() - start_time) > 100) {
            uart_put_string((char *) "Time out while waiting for DHT11 LOW response int CHECK_RESPONSE\r\n");
            return 0;
        }
    }
    end_time = timer_a_count();
}

unsigned char dht11_read_byte(void) {
    // Initilaize the byte value and the counter value
    unsigned char received_value = 0;
    unsigned char bit;

    for (bit = 8; bit > 0; bit--) {
        // Wait for the pin to go high
        start_time = end_time;
        while ( !(P1IN & DHT_DATA_PIN) ) {
            if ((timer_a_count() - start_time) > 100) {
                uart_put_string((char *) "Time out while waiting for DHT11 HIGH response int READ_BYTE\r\n");
                return 0;
            }
        }

        // Wait for the pin to go low again, with an expiration timer
        while ( P1IN & DHT_DATA_PIN ) {
            if ((timer_a_count() - start_time) > 200) {
                uart_put_string((char *) "Time out while waiting for DHT11 LOW response in READ_BYTE\r\n");
            }
        }
        end_time = timer_a_count();

        // Check if the bit was a one
        if ((end_time - start_time) > 110) {
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

    // Get the data
    dht11_send_start_signal();
    if (dht11_check_response()) {
        data.Humidity = dht11_read_byte();
        data._humidity = dht11_read_byte();
        data.Temperature = dht11_read_byte();
        data._temperature = dht11_read_byte();
        data.CheckSum = dht11_read_byte();
    } else {
        uart_put_string((char *) "No response from DHT11 on data request\r\n");
    }

    if (data.CheckSum == 0) {
        // Make sure data was received
        uart_put_string((char *) "Failure reading data from DHT11\r\n");
    } else if (!dht11_verify_checksum()) {
        // Let the user know the data is invalid
        uart_put_string((char *) "Checksum is invalid. DHT11 data is currupted\r\n");
    }

    return data;
}