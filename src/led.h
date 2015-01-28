#ifndef LED_H
#define LED_H

#include "msp430g2553.h"

#define GREEN_LED BIT6
#define RED_LED BIT0

namespace LED {

void init();

void toggleGreenLED();
void toggleRedLED();

void setGreenLED(bool on);
void setRedLED(bool on);


} // namespace

#endif // LED_H