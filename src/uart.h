#ifndef UART_H
#define UART_H

#include "msp430g2553.h"

void Configure(unsigned divider,
               unsigned char firstModulation,
               unsigned char secondModulation);

int HasData();

unsigned char Read();

void Write(unsigned char byte);

#endif