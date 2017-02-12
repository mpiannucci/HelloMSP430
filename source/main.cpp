#include <msp430.h>

#include "led.h"
#include "uart.h"

LED led;
UART uart;

void receiveDataCallback(unsigned char data) {
    led.toggle(LED::RED);
}

int main(void) {
    // Stop the Watchdog
    WDTCTL  = WDTPW + WDTHOLD;

    // Set system clock to 1MHz
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL  = CALDCO_1MHZ;

    // Initialize modules
    led.init();
    uart.init();
    uart.setRxCallback(&receiveDataCallback);

    // Enable global interrupts
    __bis_SR_register(GIE);

    // Print a message
    uart.putString("\r\nHello MSP430\r\n");

    volatile unsigned long i;

    while(1) {
        // Toggle the green led to show its still runnning
        led.toggle(LED::GREEN);

        for (i = 0; i < 50000; i++) {
            // Wait a bit
        }
    }
}