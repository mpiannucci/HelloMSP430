#include "uart.h"
#include "led.h"


int main(void) {

    // Disable watchdog timer
    WDTCTL  = WDTPW + WDTHOLD;

    // Set DCO clock to 1 MHz
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;

    // Setup LED
    LED::init();

    // Setup UART
    UART::init(104, 1, 0);

    // Write init message
    UART::writeString((char*) "Starting LED Toggle Program\n");

    for (;;) {

        // Toggle the green LED
        LED::toggleRedLED();

        // Delay a little
        for(int i=0; i< 30000; i++);
    }

    return 0;
}