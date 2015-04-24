#include <msp430.h>
#include <legacymsp430.h>

#include "uart.h"

/**
 * Receive Data (RXD) at P1.1
 * Transmit Data (TXD) at P1.2
 */
#define RXD	BIT1
#define TXD	BIT2

/**
 * Callback handler for recieving data through the UART buffer
 */
void (*uart_rx_isr_ptr)(unsigned char c);

void uart_init(void) {
    // initialize the function pointer to NULL
    uart_set_rx_isr_ptr(0L);

    // Select the recieve and transmit pins
    P1SEL  = RXD + TXD;
    P1SEL2 = RXD + TXD;

    // SMCLK
    UCA0CTL1 |= UCSSEL_2;

    // 1MHz 9600
    UCA0BR0 = 104;
    UCA0BR1 = 0;

    // Modulation UCBRSx = 1
    UCA0MCTL = UCBRS0;

    // Initialize USCI state machine
    UCA0CTL1 &= ~UCSWRST;

    // Enable USCI_A0 RX interrupt
    IE2 |= UCA0RXIE;
}

void uart_set_rx_isr_ptr(void (*isr_ptr)(unsigned char c)) {
    uart_rx_isr_ptr = isr_ptr;
}

unsigned char uart_get_character() {
    // USCI_A0 RX buffer ready? If so return the character from the buffer
    while (!(IFG2&UCA0RXIFG));
    return UCA0RXBUF;
}

void uart_put_character(unsigned char c) {
    // USCI_A0 TX buffer ready? If so, pass the next character from the buffer
    while (!(IFG2&UCA0TXIFG));
    UCA0TXBUF = c;
}

void uart_put_string(const char *str) {
    while(*str) uart_put_character(*str++);
}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void) {
    if(uart_rx_isr_ptr != 0L) {
        (uart_rx_isr_ptr)(UCA0RXBUF);
    }
}