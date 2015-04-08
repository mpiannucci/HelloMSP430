#include <msp430g2553.h>

int main(void) {
    unsigned int count;

    // Stop watchdog timer
    WDTCTL = WDTPW + WDTHOLD;

    // Configure P1 to output on P1.0
    P1OUT = 0;
    P1DIR |= BIT6 | BIT0;
    P1OUT |= BIT0;

    for(;;) {
        // Toggle P1.0 using exclusive-OR
        P1OUT ^= BIT6;
        P1OUT ^= BIT0;
        for(count=0; count<50000; count++) {
            /* Insert some delay */
        }
    }
}