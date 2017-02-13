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

class DHT11 {

public:
    /**
     * The possible error codes when reading from the DHT11 sensor
     */
    enum Error {
        NONE,
        RESPONSE_TIMEOUT,
        DATA_TIMEOUT_1,
        DATA_TIMEOUT_2,
        CHECKSUM
    };

    /**
     * Get a new instance of the DHT11 interface
     */
    DHT11();

    /**
     * Fetch the latest temperature and humidity data from the DHT11 sensor
     * @return The error code encountered when reading from the sensor. NONE indicates a successful read.
     */
    Error fetchData();

    /**
     * Verify the validity of the latest data recorded
     * @return True if valid, false otherwise
     */
    bool verifyChecksum();

    /**
     * Get the latest temperature that was read
     * @return The temperature in degrees celsius
     */
    unsigned int temperature() const;

    /**
     * Get the latest humidity that was read
     * @return The percent humidity
     */
    unsigned int humidity() const;

private:
    unsigned char _humidity;
    unsigned char _temperature;
    unsigned char _checksum;

    unsigned char __humidity__;
    unsigned char __temperature__;
};

#endif // DHT11_H
