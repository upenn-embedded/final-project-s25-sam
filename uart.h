#ifndef UART_H
#define UART_H

#include <avr/io.h>
#include <stdio.h>  // <-- ADD THIS LINE

void uart_init(void);
void uart_transmit(unsigned char data);
unsigned char uart_receive(void);
int uart_putchar(char c, FILE *stream);

#endif


