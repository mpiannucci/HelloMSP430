#include "dht11.h"
#include <msp430.h>

#define DHT_DATA_PIN BIT4

unsigned int dht11_verify_checksum(dht11_data* data) {
    if (data->checkSum == ((data->humidity + data->temperature + data->_humidity + data->_temperature) & 0xFF)) {
        return 1;
    } else {
        return 0;
    }
}

dht11_error dht11_get_data(dht11_data* data) {
    unsigned char raw[6];
    const unsigned char raw_count = 6;
    unsigned char raw_index = 0;
    register unsigned char mask = 1;
    register unsigned start_time, end_time;

    // Setup the timer
    TACTL = TASSEL_2 + MC_2;

    // Initialize the data container
    data->humidity = 0;
    data->_humidity = 0;
    data->temperature = 0;
    data->_temperature = 0;
    data->checkSum = 0;

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
            raw[raw_index] |= mask;
        }

        if (!(mask >>= 1)) {
            mask = 0x80, ++raw_index;
        }
    } while ( raw_index < raw_count );

    data->humidity = raw[1];
    data->_humidity = raw[2];
    data->temperature = raw[3];
    data->_temperature = raw[4];
    data->checkSum = raw[5];

    if (data->checkSum == 0) {
        // Make sure data was received
        return CHECKSUM;
    } else if (!dht11_verify_checksum(data)) {
        // Let the user know the data is invalid
        return CHECKSUM;
    }

    return NONE;
}

int read_dht(unsigned char *p)
{
    TACTL = TASSEL_2 | MC_2;
    // Note: TimerA must be continuous mode (MC_2) at 1 MHz
    const unsigned b = BIT4;                                    // I/O bit
    const unsigned char *end = p + 6;                           // End of data buffer
    register unsigned char m = 1;                               // First byte will have only start bit
    register unsigned st, et;                                   // Start and end times
    //
    p[0] = p[1] = p[2] = p[3] = p[4] = p[5] = 0;                // Clear data buffer
    //
    P1OUT &= ~b;                                                // Pull low
    P1DIR |= b;                                                 // Output
    P1REN &= ~b;                                                // Drive low
    st = TAR;
    while((TAR - st) < 18000);                        // Wait 18 ms
    P1REN |= b;                                                 // Pull low
    P1OUT |= b;                                                 // Pull high
    P1DIR &= ~b;                                                // Input
    //
    st = TAR;                                                   // Get start time for timeout
    while(P1IN & b) if((TAR - st) > 100) return -1;             // Wait while high, return if no response
    et = TAR;                                                   // Get start time for timeout
    do {                                                        //
        st = et;                                                // Start time of this bit is end time of previous bit
        while(!(P1IN & b)) if((TAR - st) > 100) return -2;      // Wait while low, return if stuck low
        while(P1IN & b) if((TAR - st) > 200) return -3;         // Wait while high, return if stuck high
        et = TAR;                                               // Get end time
        if((et - st) > 110) *p |= m;                            // If time > 110 us, then it is a one bit
        if(!(m >>= 1)) m = 0x80, ++p;                           // Shift mask, move to next byte when mask is zero
    } while(p < end);                                           // Do until array is full
    //
    p -= 6;                                                     // Point to start of buffer
    if(p[0] != 1) return -4;                                    // No start bit
    if(((p[1] + p[2] + p[3] + p[4]) & 0xFF) != p[5]) return -5; // Bad checksum
    //
    return 0;                                                   // Good read
}
