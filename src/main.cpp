#include "msp430g2553.h"


int main(void) {
    volatile int i;

    WDTCTL = WDTPW + WDTHOLD;         // Stop watchdog timer
    P1DIR = P1DIR | 0x01;             // Set P1.0 to output direction
    // Note: 0x01 = 0000 0001 binary (the LSB is set).

    for (;;) {                        // Do this forever (ha)
        P1OUT = P1OUT ^ 0x01;         // Toggle P1.0 using exclusive-OR
        for (i=1; i<30000; i=i+1) {}  // Delay
    }
    return 0;
}