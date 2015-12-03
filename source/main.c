#include <msp430.h>

#include "uart.h"
#include "led.h"
#include "dht11.h"

volatile unsigned char temp_requested = 0;

void uart_rx_isr(unsigned char c) {
    uart_put_string((char *) "Recieved data request from master!\r\n");
    led_toggle_red_state();

    if (!temp_requested) {
        temp_requested = 1;
    }
}

int read_dht(unsigned char *p)
{
    TACTL = TASSEL_2 | MC_2;
    // Note: TimerA must be continuous mode (MC_2) at 1 MHz
    const unsigned b = BIT4;                                    // I/O bit
    const unsigned char *end = p + 6;                           // End of data buffer
    register unsigned char m = 1;                               // First byte will have only start bit
    register unsigned st, et;                                   // Start and end times
    //
    p[0] = p[1] = p[2] = p[3] = p[4] = p[5] = 0;                // Clear data buffer
    //
    P1OUT &= ~b;                                                // Pull low
    P1DIR |= b;                                                 // Output
    P1REN &= ~b;                                                // Drive low
    st = TAR;
    while((TAR - st) < 18000);                        // Wait 18 ms
    P1REN |= b;                                                 // Pull low
    P1OUT |= b;                                                 // Pull high
    P1DIR &= ~b;                                                // Input
    //
    st = TAR;                                                   // Get start time for timeout
    while(P1IN & b) if((TAR - st) > 100) return -1;             // Wait while high, return if no response
    et = TAR;                                                   // Get start time for timeout
    do {                                                        //
        st = et;                                                // Start time of this bit is end time of previous bit
        while(!(P1IN & b)) if((TAR - st) > 100) return -2;      // Wait while low, return if stuck low
        while(P1IN & b) if((TAR - st) > 200) return -3;         // Wait while high, return if stuck high
        et = TAR;                                               // Get end time
        if((et - st) > 110) *p |= m;                            // If time > 110 us, then it is a one bit
        if(!(m >>= 1)) m = 0x80, ++p;                           // Shift mask, move to next byte when mask is zero
    } while(p < end);                                           // Do until array is full
    //
    p -= 6;                                                     // Point to start of buffer
    if(p[0] != 1) return -4;                                    // No start bit
    if(((p[1] + p[2] + p[3] + p[4]) & 0xFF) != p[5]) return -5; // Bad checksum
    //
    return 0;                                                   // Good read
}

int main(void) {
    // Stop the Watchdog
    WDTCTL  = WDTPW + WDTHOLD;

    // Set system clock to 1MHz
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL  = CALDCO_1MHZ;

    // Initialize modules
    led_init();
    uart_init();
    //dht11_init();

    // register ISR called when data was received
    uart_set_rx_isr_ptr(uart_rx_isr);

    // Enable global interrupts
    __bis_SR_register(GIE);

    uart_put_string((char *) "\r\n********************************\r\n");
    uart_put_string((char *) "Hello MSP430\r\n");
    uart_put_string((char *) "Enter any key to toggle the LED\r\n");
    uart_put_string((char *) "and read the temperature\r\n");
    uart_put_string((char *) "********************************\r\n\r\n");

    volatile unsigned long i;

    while(1) {
        // Toggle the green led to show its still runnning
        led_toggle_green_state();

        for (i = 0; i < 50000; i++) {
            // Check if the temperature was requested.
            if (temp_requested) {
                //unsigned char dht[6];
                dht11_data* data;
                dht11_error error = dht11_get_data(data);
                if (error != NONE) {
                    uart_put_string((char*) "Errror\r\n");
                } else {
                    uart_put_string((char *) "Got Data\r\n");
                }
                temp_requested = 0;
            }
        }
    }
}