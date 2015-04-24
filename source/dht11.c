#include "dht11.h"
#include <msp430.h>

void dht11_init() {
    // Set the time to 5 Hz
    TACCR0 = 50000;

    // Enable interrupt
    TACCTL0 = CCIE;

    // SMCLK, div 4, up mode,
    TA0CTL = TASSEL_2 + ID_2 + MC_1 + TACLR;
}

void dht11_set_timer_isr_ptr(void (*isr_ptr)(void)) {

}

void dht11_send_start_signal(void) {

}

unsigned int dht11_check_response(void) {
    return 1;
}

unsigned int dht11_read_byte(void) {
    return 1;
}

unsigned int dht11_verify_checksum() {
    return 1;
}

unsigned int* dht11_get_data(void) {
    return 0;
}