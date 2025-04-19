#include <avr/io.h>        // Standard I/O definitions for AVR
#include <avr/interrupt.h> // Interrupts
#include <avr/sleep.h>     // Sleep modes (not used here, but included)
#include <stdlib.h>        // General utilities
#include <stdio.h>         // Standard I/O (e.g., printf)

#define F_CPU 16000000UL  // ? Set CPU frequency to 16 MHz
#include <util/delay.h>   // Delay utilities

// UART library (custom or provided) for serial communication
#include "uart.h"

// === Constants & Macros ===
#define BAUD 9600  // UART Baud rate
#define BAUD_PRESCALE (((F_CPU / (BAUD * 16UL))) - 1)  // ? Recalculates correctly for 16 MHz

/** Ultrasonic sensor */

volatile uint16_t timer_count = 0;     // Captured echo duration
volatile uint8_t measurementReady = 0; // Flag for when ultrasonic measurement is ready
volatile uint8_t rising_edge = 1;

void init_ultrasonic() {
    // Timer1, prescale 64
    TCCR1B |= (1 << CS11);
    TCCR1B |= (1 << CS10);

    // Set Timer 1 to Normal
    TCCR1A &= ~(1 << WGM10);
    TCCR1A &= ~(1 << WGM11);
    TCCR1B &= ~(1 << WGM12);

    DDRB |= (1 << DDB1); // set PB1 as output (trig)
    DDRB &= ~(1 << DDB0); // set PB0 as input (echo)

    TIFR1 |= (1 << ICF1); // clear input capture flag
}
 
void send_trigger_pulse() {
    DDRB |= (1 << PB1);
    PORTB |= (1 << PB1);
    _delay_us(10);
    PORTB &= ~(1 << PB1);
}

void prepare_for_ultrasonic_measurement() {
    TIFR1 |= (1 << ICF1); // clear any previous interrupt flag
    measurementReady = 0;
    TIMSK1 |= (1 << ICIE1); // turn on input capture
    TCCR1B |= (1 << ICES1); // rising edge detection
    rising_edge = 1;
}

volatile uint16_t start_time = 0;
ISR(TIMER1_CAPT_vect) {
    if (rising_edge) {
        start_time = ICR1;
        printf("Rising edge detected\n");
        TCCR1B &= ~(1 << ICES1); // switch to falling edge detection
        rising_edge = 0;
    } else {
        timer_count = ICR1 - start_time;
        TCCR1B |= (1 << ICES1);
        measurementReady = 1;
        rising_edge = 1;
        printf("Falling edge\n");
        TIMSK1 &= ~(1 << ICIE1); // disable interrupts
    }
    TIFR1 |= (1 << ICF1); // clear
}

int echo_to_cm(int echo_ticks) {
    // echo_time is in ticks
    // 16 MHz / 64 = 250000 Hz
    // 0.000004 seconds per tick
    // one microsecond is 0.25 ticks
    // one tick is 4 uS
    
    int uS = echo_ticks * 4;
    int cm = uS / 58;
    return cm;
}


int main(void) {
    init_ultrasonic();
    uart_init();
    sei(); 
    
    while (1) {
        prepare_for_ultrasonic_measurement();
        send_trigger_pulse();
        _delay_ms(600);

        if (measurementReady) {
            printf("Ultrasonic %d ticks : %d cm\n", timer_count, echo_to_cm(timer_count));
        } else {
            printf("Measurement not ready in time!\n");
        }
    }
}