#include "timer.h"
#include <msp430.h>

void (*timer_a_isr_ptr)(void);

void timer_a_init(void) {
    // Initialize the timer to count at 5Hz
    TACCR0 = 50000;

    // SMCLK, div 4, up mode, clear
    TA0CTL = TASSEL_2 + ID_2 + MC_1 + TACLR;

    // Enable timer interupts adn initialize the callback pointer ot NULL
    timer_a_set_isr(0L);
    timer_a_enable_isr(1);
}

void timer_a_set_isr(void (*isr_ptr)(void)) {
    timer_a_isr_ptr = isr_ptr;
}

void timer_a_set_count(int count) {
    TACCR0 |= count;
}

void timer_a_start(Timer_Mode mode) {
    switch (mode) {
    case UP:
        TA0CTL |= MC_1;
        break;
    case UP_CONTINUOUS:
        TA0CTL |= MC_2;
        break;
    case UP_DOWN:
        TA0CTL |= MC_3;
        break;
    default:
        break;
    }
}

void timer_a_stop(void) {
    TA0CTL &= ~(MC_3);
}

void timer_a_reset(void) {
    TACTL |= TACLR;
}

void timer_a_enable_isr(int enable) {
    if (enable > 0) {
        TACCTL0 |= CCIE;
    } else {
        TACCTL0 &= ~(CCIE);
    }
}

void timer_a_clear_isr_flag() {
    TACCTL0 &= ~(CCIFG);
}

unsigned char timer_a_count(void) {
    return TAR;
}


#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void) {
    if (timer_a_isr_ptr != 0L) {
        // Call the interrupt function
        (timer_a_isr_ptr)();
    }

    // Clear the interrupt waiting flag
    TACCTL0 &= ~(CCIFG);
}