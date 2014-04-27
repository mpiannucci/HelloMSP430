#include "msp430g2553.h"

volatile unsigned int i; // volatile to prevent optimization

int main(void) {
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    P1DIR |= 0x01; // Set P1.0 to output direction
    for (;;)
    {
        1OUT ˆ= 0x01; // Toggle P1.0 using exclusive-OR
        i = 50000; // Delay
        do (i--);
            while (i != 0);
    }
    return 0;
}