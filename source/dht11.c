#include "dht11.h"
#include <msp430.h>

#define DHT_DATA_PIN BIT4

unsigned int dht11_verify_checksum(dht11_data* data) {
    if (data->checksum == ((data->humidity + data->temperature + data->_humidity + data->_temperature) & 0xFF)) {
        return 1;
    } else {
        return 0;
    }
}

dht11_error dht11_get_data(dht11_data* data) {
    unsigned char raw[6];
    const unsigned char raw_count = 6;
    unsigned char* raw_ptr = &raw[0];
    unsigned char* raw_end = raw_ptr + raw_count;
    //unsigned char raw_index = 0;
    register unsigned char mask = 1;
    register unsigned start_time, end_time;

    // Setup the timer
    TACTL = TASSEL_2 + MC_2;

    // Initialize the data container
    data->humidity = 0;
    data->_humidity = 0;
    data->temperature = 0;
    data->_temperature = 0;
    data->checksum = 0;

    // Initialize the raw data
    raw[0] = raw[1] = raw[2] = raw[3] = raw[4] = raw[5] = 0;

    // Set the pin low
    P1OUT &= ~(DHT_DATA_PIN);

    // Set the pin to output mode
    P1DIR |= DHT_DATA_PIN;

    // Drive the pull up low
    P1REN &= ~(DHT_DATA_PIN);

    // Delay for 18ms
    start_time = TAR;
    while ((TAR - start_time) < 18000);

    // Set the pin high
    P1REN |= DHT_DATA_PIN;
    P1OUT |= DHT_DATA_PIN;

    // Set the direction to input mode to prepare for the response
    P1DIR &= ~(DHT_DATA_PIN);

    // Wait for the signal to go high or for the timer to expire
    start_time = TAR;
    while ( P1IN & DHT_DATA_PIN ) {
        if ((TAR - start_time) > 100) {
            return RESPONSE_TIMEOUT;
        }
    }
    end_time = TAR;

    // Read the bits
    do {
        // Wait for the pin to go high
        start_time = end_time;
        while ( !(P1IN & DHT_DATA_PIN) ) {
            if ((TAR - start_time) > 100) {
                return DATA_TIMEOUT;
            }
        }

        // Wait for the pin to go low again, with an expiration timer
        while ( P1IN & DHT_DATA_PIN ) {
            if ((TAR - start_time) > 200) {
                return DATA_TIMEOUT;
            }
        }
        end_time = TAR;

        // Check if the bit was a one
        if ((end_time - start_time) > 110) {
            *raw_ptr |= mask;
        }

        if (!(mask >>= 1)) {
            mask = 0x80, ++raw_ptr;
        }
    } while ( raw_ptr < raw_end );

    data->humidity = raw[1];
    data->_humidity = raw[2];
    data->temperature = raw[3];
    data->_temperature = raw[4];
    data->checksum = raw[5];

    if (data->checksum == 0) {
        // Make sure data was received
        return CHECKSUM;
    } else if (!dht11_verify_checksum(data)) {
        // Let the user know the data is invalid
        return CHECKSUM;
    }

    return NONE;
}
