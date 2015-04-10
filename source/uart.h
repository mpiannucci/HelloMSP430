#ifndef UART_H
#define UART_H

/**
 * Initialize UART.
 */
void uart_init(void);

/**
 * Set function pointer for ISR to call when data was received.
 *
 * @param[in] *isr_ptr	Function pointer to call when ISR received.
 */
void uart_set_rx_isr_ptr(void (*isr_ptr)(unsigned char c));

/**
 * Read one character from the UART buffer.
 *
 * @return The character received.
 */
unsigned char uart_get_character();

/**
 * Write one chracter to the UART buffer.
 *
 * @param[in] c	The character to write.
 */
void uart_put_character(unsigned char c);

/**
 * Write string to the UART buffer.
 *
 * @param[in] c The string to write to the buffer. Must be terminated by \0.
 */
void uart_put_string(const char *str);

#endif // UART_H