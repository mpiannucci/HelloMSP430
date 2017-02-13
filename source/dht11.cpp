#include "dht11.h"
#include <msp430.h>

#define DHT_DATA_PIN BIT4

DHT11::DHT11() :
    _temperature(0),
    _humidity(0),
    _checksum(0) {

}

DHT11::Error DHT11::fetchData() {
    unsigned char raw[6];
    const unsigned char raw_count = 6;
    unsigned char* raw_ptr = &raw[0];
    unsigned char* raw_end = raw_ptr + raw_count;
    //unsigned char raw_index = 0;
    register unsigned char mask = 1;
    register unsigned start_time, end_time;

    // Setup the timer
    TACTL = TASSEL_2 + MC_2;

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
                return DATA_TIMEOUT_1;
            }
        }

        // Wait for the pin to go low again, with an expiration timer
        while ( P1IN & DHT_DATA_PIN ) {
            if ((TAR - start_time) > 200) {
                return DATA_TIMEOUT_2;
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

    _humidity = raw[1];
    __humidity__ = raw[2];
    _temperature = raw[3];
    __temperature__ = raw[4];
    _checksum = raw[5];

    if (_checksum == 0) {
        // Make sure data was received
        return CHECKSUM;
    } else if (!verifyChecksum()) {
        // Let the user know the data is invalid
        return CHECKSUM;
    }

    return NONE;
}

bool DHT11::verifyChecksum() {
    return (_checksum == ((_humidity + _temperature + __humidity__ + __temperature__) & 0xFF));
}

unsigned int DHT11::temperature() const {
    return _temperature;
}

unsigned int DHT11::humidity() const {
    return _humidity;
}
