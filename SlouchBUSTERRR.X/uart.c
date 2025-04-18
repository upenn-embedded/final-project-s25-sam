/* 
 * File:   uart.c
 * Author: saanvimmehta
 *
 * Created on April 7, 2025, 1:10 PM
 */

#include "uart.h"
#include <stdio.h>

#define F_CPU 16000000UL  // ? Match main.c
#define BAUD 9600
#define BAUD_PRESCALE (((F_CPU / (BAUD * 16UL))) - 1)


static FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

void uart_init(void) {
    // Set baud rate
    UBRR0H = (unsigned char)(BAUD_PRESCALE >> 8);
    UBRR0L = (unsigned char)BAUD_PRESCALE;

    // Enable transmitter and receiver
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    // Set frame format: 8 data bits, 1 stop bit
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

    // Redirect stdout to UART for printf support
    stdout = &uart_output;
}

void uart_transmit(unsigned char data) {
    // Wait until buffer is empty
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

unsigned char uart_receive(void) {
    // Wait for data to be received
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}

// Required for printf to send data via UART
int uart_putchar(char c, FILE *stream) {
    if (c == '\n') {
        uart_putchar('\r', stream);  // Send carriage return before newline
    }
    uart_transmit(c);
    return 0;
}
