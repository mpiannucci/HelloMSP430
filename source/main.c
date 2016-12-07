#include <msp430.h>

#include "uart.h"
#include "led.h"
#include "dht11.h"

volatile unsigned char temp_requested = 0;

void uart_rx_isr(unsigned char c) {
    led_toggle_red_state();

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
    led_init();
    uart_init();

    // register ISR called when data was received
    uart_set_rx_isr_ptr(uart_rx_isr);

    // Enable global interrupts
    __bis_SR_register(GIE);

    uart_put_string((char *) "\r\n********************************\r\n");
    uart_put_string((char *) "Hello MSP430\r\n");
    uart_put_string((char *) "Enter any key to toggle the LED\r\n");
    uart_put_string((char *) "and read the temperature\r\n");
    uart_put_string((char *) "********************************\r\n\r\n");

    volatile unsigned long i;

    while(1) {
        // Toggle the green led to show its still runnning
        led_toggle_green_state();

        for (i = 0; i < 50000; i++) {
            // Check if the temperature was requested.
            if (temp_requested) {
                dht11_data data;
                dht11_error error = dht11_get_data(&data);
                if (error == CHECKSUM) {
                    uart_put_string((char*) "Bad DHT Checksum\r\n");
                } else if (error == RESPONSE_TIMEOUT) {
                    uart_put_string((char*) "DHT Response Timeout\r\n");
                } else if (error == DATA_TIMEOUT) {
                    uart_put_string((char*) "DHT Data Timeout\r\n");
                } else {
                    char temp[20];
                    char humidity[20];
                    sprintf(temp, "Temperature: %u C\r\n", data.temperature);
                    sprintf(humidity, "Humidity: %u \%\r\n", data.humidity);
                    uart_put_string(temp);
                    uart_put_string(humidity);
                }
                temp_requested = 0;
            }
        }
    }
}