#include "dht11.h"
#include <msp430.h>

DHT11_Data data;

void (*dht11_timer_isr_ptr)(void);

void dht11_init() {
    // Set the time to 5 Hz
    TACCR0 = 50000;

    // Enable interrupt
    TACCTL0 = CCIE;

    // SMCLK, div 4, up mode,
    TA0CTL = TASSEL_2 + ID_2 + MC_1 + TACLR;
}

void dht11_set_timer_isr_ptr(void (*isr_ptr)(void)) {
    dht11_timer_isr_ptr = isr_ptr;
}

void dht11_send_start_signal(void) {
    // TODO: Send the start signal to the device
}

unsigned int dht11_check_response(void) {
    // TODO: Recieve the response to the start signal

    return 1;
}

unsigned int dht11_read_byte(void) {
    // TODO: Receive the pending byte from the device

    return 1;
}

unsigned int dht11_verify_checksum() {
    if (data.CheckSum == (data.Humidity + data.Temperature + data._humidity + data._temperature)) {
        return 1;
    } else {
        return 0;
    }
}

DHT11_Data dht11_get_data(void) {
    dht11_send_start_signal();
    if (dht11_check_response()) {
        data.Humidity = dht11_read_byte();
        data._humidity = dht11_read_byte();
        data.Temperature = dht11_read_byte();
        data._temperature = dht11_read_byte();
        data.CheckSum = dht11_read_byte();
    }
    return data;
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void CCR0_ISR(void) {
    if (dht11_timer_isr_ptr != 0L) {
        (dht11_timer_isr_ptr)();
    }
}