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
typedef struct DHT11_Data {
    unsigned char Humidity;
    unsigned char Temperature;
    unsigned char CheckSum;

    unsigned char _humidity;
    unsigned char _temperature;
} DHT11_Data;

/**
 * Initialize the DHT11 driver
 */
void dht11_init(void);

/**
 * Send the start signal to tell the device to prepare to send data.
 */
static void dht11_send_start_signal(void);

/**
 * Get the response to the start signal being received by the device
 *
 * @return  1 if ready to send data, 0 otherwise
 */
static unsigned int dht11_check_response(void);

/**
 * Read a data byte from the device. Assumes the start signal and rcheck response have both been executed
 *
 * @return  The byte read from the device
 */
static unsigned char dht11_read_byte(void);

/**
 * Verify that the data was received correctly.
 *
 * @return  1 if the data received matches the checksum, 0 otherwise
 */
unsigned int dht11_verify_checksum(void);

/**
 * Get a packet of data from the device.
 * This function will send the start signal, check the response, and then read the data into a DHT11_Data
 * structure. This way, the user can simply call one function to receive all data. If you want to verify the
 * data, call dht_verify_checksum after this function, but before reading another packet.
 *
 * @return  A data structure holding the data received from the device
 */
DHT11_Data dht11_get_data(void);

/**
 * Handler for the timer interrupt.
 */
void dht11_isr_callback(void);

#endif // DHT11_H
