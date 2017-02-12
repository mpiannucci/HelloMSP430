#include <msp430.h>

#include "led.h"


int main(void) {
    // Stop the Watchdog
    WDTCTL  = WDTPW + WDTHOLD;

    // Set system clock to 1MHz
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL  = CALDCO_1MHZ;

    // Initialize modules
    LED led;

    volatile unsigned long i;

    while(1) {
        // Toggle the green led to show its still runnning
        led.toggle(LED::GREEN);

        for (i = 0; i < 50000; i++) {
            // Wait a bit
        }
    }
}