#include <msp430.h>

#include "uart.h"

/**
 * Receive Data (RXD) at P1.1
 * Transmit Data (TXD) at P1.2
 */
#define RXD	BIT1
#define TXD	BIT2

UART::RxCallback UART::_rxCallback = 0L;
bool UART::initialized = false;

UART::UART() {

}

void UART::init() {
    if (initialized) {
        return;
    }

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

    initialized = true;
}

void UART::setRxCallback(RxCallback callback) {
    _rxCallback = callback;
}

UART::RxCallback UART::rxCallback() {
    return _rxCallback;
}

unsigned char UART::getCharacter() {
    // USCI_A0 RX buffer ready? If so return the character from the buffer
    while (!(IFG2&UCA0RXIFG));
    return UCA0RXBUF;
}

void UART::putCharacter(unsigned char c) {
    // USCI_A0 TX buffer ready? If so, pass the next character from the buffer
    while (!(IFG2&UCA0TXIFG));
    UCA0TXBUF = c;
}

void UART::putString(const char* str) {
    while(*str) putCharacter(*str++);
}

__attribute__ ((interrupt(USCIAB0RX_VECTOR)))
void USCI0RX_ISR(void) {
    if (UART::rxCallback() != 0L) {
        (UART::rxCallback())(UCA0RXBUF);
    }
}