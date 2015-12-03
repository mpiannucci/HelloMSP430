/**
 * dht11.h
 *
 * Module for interfacing a DHT11 Temperature and Humidity Sensor.
 * This module communicates with the device on pin 2.4 using GPIO. It also requires the
 * timer A0 to communicate reliably with the device. This library is written using the
 * reference material at http://www.micropik.com/PDF/dht11.pdf.
 *
 * @author Matthew Iannucci, 2015
 *
 */

#ifndef DHT11_H
#define DHT11_H

/**
 * Data structure to hold received data from the DHT11 temperature sensor
 */
typedef struct dht11_data {
    unsigned char humidity;
    unsigned char _humidity;
    unsigned char temperature;
    unsigned char _temperature;
    unsigned char checkSum;

} dht11_data;

typedef enum {
    NONE,
    RESPONSE_TIMEOUT,
    DATA_TIMEOUT,
    CHECKSUM
} dht11_error;

/**
 * Verify that the data was received correctly.
 *
 * @return  1 if the data received matches the checksum, 0 otherwise
 */
unsigned int dht11_verify_checksum(dht11_data* data);

/**
 * Get a packet of data from the device.
 * This function will send the start signal, check the response, and then read the data into a dht11_data
 * structure. This way, the user can simply call one function to receive all data. If you want to verify the
 * data, call dht_verify_checksum after this function, but before reading another packet.
 * @param  data The pointer of type dht11_data for the new data to be read into
 * @return  The error message as the dht11_error type
 */
dht11_error dht11_get_data(dht11_data* data);

int read_dht(unsigned char *p);

#endif // DHT11_H
