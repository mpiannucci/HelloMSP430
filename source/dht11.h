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
 * Set the ISR function pointer for the internal timer used when reading data
 */
void dht11_set_timer_isr_ptr(void (*isr_ptr)(void));

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

#endif // DHT11_H
