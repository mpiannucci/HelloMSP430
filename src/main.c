#include <msp430.h>

int main(void) {
    unsigned int count;
    WDTCTL = WDTPW + WDTHOLD; //Stop watchdog timer

    P1OUT = 0; //Configure P1 to output on P1.0
    P1DIR |= 0x01;

    for(;;) {
        P1OUT ^= 0x01; //Toggle P1.0 using exclusive-OR
        for(count=0; count<10000; count++) {
            /* Insert some delay */
        }
    }
}