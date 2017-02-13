#include <msp430.h>
#include <stdio.h>

#include "led.h"
#include "uart.h"
#include "dht11.h"

volatile unsigned char temp_requested = 0;

LED led;
UART uart;
DHT11 dht;

void receiveDataCallback(unsigned char data) {
    // led.toggle(LED::RED);

    if (!temp_requested) {
        temp_requested = 1;
    }
}

int main(void) {
    // Stop the Watchdog
    WDTCTL  = WDTPW + WDTHOLD;

    // Set system clock to 1MHz
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL  = CALDCO_1MHZ;

    // Initialize modules
    led.init();
    uart.init();
    uart.setRxCallback(&receiveDataCallback);

    // Enable global interrupts
    __bis_SR_register(GIE);

    // Print a message
    uart.putString("\r\nHello MSP430\r\n");
    uart.putString("Enter any key to toggle the red LED\r\n");
    uart.putString("and read the temperature!");

    volatile unsigned long i;

    while(1) {
        // Toggle the green led to show its still runnning
        led.toggle(LED::GREEN);

        for (i = 0; i < 10000; i++) {
            // Wait a bit

            if (temp_requested) {
                DHT11::Error error = dht.fetchData();
                if (error == DHT11::CHECKSUM) {
                    uart.putString("Bad DHT Checksum\r\n");
                } else if (error == DHT11::RESPONSE_TIMEOUT) {
                    uart.putString("DHT Response Timeout\r\n");
                } else if (error == DHT11::DATA_TIMEOUT_1) {
                    uart.putString("DHT Data Timeout 1\r\n");
                } else if (error == DHT11::DATA_TIMEOUT_2) {
                    uart.putString("DHT Data Timeout 2\r\n");
                } else {
                    char temp[20];
                    char humidity[20];
                    sprintf(temp, "Temperature: %u C\r\n", dht.temperature());
                    sprintf(humidity, "Humidity: %u \%\r\n", dht.humidity());
                    uart.putString(temp);
                    uart.putString(humidity);
                }

                temp_requested = 0;
            }
        }
    }
}