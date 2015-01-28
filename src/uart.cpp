#include "uart.h"

void UART::init(unsigned divider,
                unsigned char firstModulation,
                unsigned char secondModulation) {
    P1SEL |= BIT1 | BIT2;
    P1SEL2 |= BIT1 | BIT2;

    UCA0CTL1 = UCSSEL_2;
    UCA0BR0 = divider & 0xFF;
    UCA0BR1 = divider >> 8;
    UCA0MCTL = ((firstModulation  & 0xF) << 4) |
               ((secondModulation & 0x7) << 1);
    UCA0CTL1 &= ~UCSWRST;
}

bool UART::hasData() {
    return IFG2 & UCA0RXIFG;
}

unsigned char UART::readByte() {
    while (!(IFG2 & UCA0RXIFG));
    return UCA0RXBUF;
}

void UART::writeByte(unsigned char byte) {
    while (!(IFG2 & UCA0TXIFG));
    UCA0TXBUF = byte;
}

void UART::writeString(const char* string) {
    while(*string)
        writeByte(*string++);
}