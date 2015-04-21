#include <msp430.h>

#include "uart.h"
#include "led.h"

void uart_rx_isr(unsigned char c) {
    uart_put_string((char *) "Recieved signal!\r\n");
    led_toggle_red_state();
}

int main(void) {
    // Stop the Watchdog
    WDTCTL  = WDTPW + WDTHOLD;

    // Set system clock to 1MHz
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL  = CALDCO_1MHZ;

    led_init();
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
        led_toggle_green_state();

        for (i = 0; i < 50000; i++) {
            // Do nothing, just delay
        }
    }
}