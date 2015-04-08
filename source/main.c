#include <msp430g2553.h>

int main(void) {
    unsigned int count;
    WDTCTL = WDTPW + WDTHOLD; //Stop watchdog timer

    //Configure P1 to output on P1.0
    P1OUT = 0;
    P1DIR |= 0x01;

    for(;;) {
        //Toggle P1.0 using exclusive-OR
        P1OUT ^= 0x01;
        for(count=0; count<20000; count++) {
            /* Insert some delay */
        }
    }
}