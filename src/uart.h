#ifndef UART_H
#define UART_H

#include "msp430g2553.h"

namespace UART {

void init(unsigned divider,
          unsigned char firstModulation,
          unsigned char secondModulation);

bool hasData();

unsigned char readByte();

void writeByte(unsigned char byte);

void writeString(const char* string);

} // namespace

#endif