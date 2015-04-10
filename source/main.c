#include <msp430.h>

#include "uart.h"

void uart_rx_isr(unsigned char c) {
    uart_put_string((char *) "Recieved signal!\r\n");
    P1OUT ^= BIT0;
}

/**
 * Main routine
 */
int main(void)
{
    WDTCTL  = WDTPW + WDTHOLD;  // Stop WDT
    BCSCTL1 = CALBC1_1MHZ;      // Set DCO
    DCOCTL  = CALDCO_1MHZ;

    P1DIR  = BIT0 + BIT6;       // P1.0 and P1.6 are the red+green LEDs
    P1OUT  = BIT0 + BIT6;       // All LEDs off

    uart_init();

    // register ISR called when data was received
    uart_set_rx_isr_ptr(uart_rx_isr);

    __bis_SR_register(GIE);

    uart_put_string((char *) "\n\r***************\n\r");
    uart_put_string((char *) "Hello MSP430\n\r");
    uart_put_string((char *) "Enter any key to toggle the LED\r\n");
    uart_put_string((char *) "***************\n\r\n\r");

    volatile unsigned long i;

    while(1) {
        // Toggle the green led to show its still runnning
        P1OUT ^= BIT6;

        for (i = 0; i < 50000; i++) {
            // Do nothing, just delay
        }
    }
}