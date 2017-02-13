/**
 * uart.h
 *
 * Module for controlling the UART aboard the MSP430.
 * This module uses the hardware UART by defualt. To communicate through the usb
 * port on the Launchpad, be sure that the jumpers on the Launchpad are crossed to HW mode.
 *
 * HW ==|||
 * SW |||||
 *
 * @author Matthew Iannucci, 2015
 *
 */

#ifndef UART_H
#define UART_H

class UART {

public:
    /**
     * A callback for receiving data through the UART
     */
    typedef void (*RxCallback)(unsigned char c);

    /**
     * Constructor
     */
    UART();

    /**
     * Initializes the UART, will only occur once
     */
    void init();

    void enableRxInterrupt();

    void disableRxInterrupt();

    /**
     * Sets the interrupt for data being received through the UART
     * @param callback The function to call as in interrupt handler
     */
    static void setRxCallback(RxCallback callback);

    /**
     * Get the rx interrupt callback
     * @return The rx interrupt callback
     */
    static RxCallback rxCallback();

    /**
     * Gets the first character in the RX buffer
     * @return The first character read through RX
     */
    unsigned char getCharacter();

    /**
     * Send a character through the TX buffer
     * @param c The character to send
     */
    void putCharacter(unsigned char c);

    /**
     * Send a string through the TX buffer
     * @param str The string to send
     */
    void putString(const char* str);

private:
    static RxCallback _rxCallback;
    static bool initialized;
};

#endif // UART_H