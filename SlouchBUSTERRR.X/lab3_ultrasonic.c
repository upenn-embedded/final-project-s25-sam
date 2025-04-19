/* 
 * File:   part_c.c
 * Author: mcnic
 *
 * Created on March 6, 2025, 4:15 PM
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "uart.h"
#include <string.h>
#include <stdlib.h>

volatile int looking_for_rising = 0;
volatile int echo_ticks = 0;
volatile int decode_echo = 0;
volatile int us = 0;
volatile int rising = 0;
volatile int falling = 0;
volatile int distance_read = 0;

void Initialize() {
    
    cli();
    
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
            
    sei(); // enable global interrupts
    
}


// input capture interrupt
ISR(TIMER1_CAPT_vect) {
    
    if (looking_for_rising) {
        TCNT1 = 0; // reset timer
        TCCR1B &= ~(1 << ICES1); // switch to falling edge detection
        looking_for_rising = 0;
    } 
    else { // looking for echo falling edge  
        TIMSK1 &= ~(1 << ICIE1); // disable input capture interrupt
        echo_ticks = ICR1; // time of echo pulse
        TCCR1B |= (1 << ICES1); // look for rising edge
        looking_for_rising = 1;
        distance_read = 1;
    }
    
    TIFR1 |= (1 << ICF1); // clear input capture flag

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

int us_to_cm(int us) {
    int cm = us / 58;
    return cm;
}

void prepare_for_ultrasonic_measurement() {
    distance_read = 0;
    looking_for_rising = 1;
    TIMSK1 |= (1 << ICIE1); // enable input capture interrupt
    TCCR1B |= (1 << ICES1); // look for rising edge
}

void send_trigger_pulse() {
    // 10 uS pulse
    PORTB |= (1 << PB1);
    _delay_us(10);
    PORTB &= ~(1 << PB1);
}

/*
 * 
 */
int main() {
    
    uart_init();
    Initialize();
    printf("start!\n");

    while(1) {
        prepare_for_ultrasonic_measurement();
        send_trigger_pulse();

        while (!distance_read) {
            // busy wait
        }

        int cm = echo_to_cm(echo_ticks);
        
        printf("cm: %d\n", cm);
        
        _delay_ms(1000); // do this once every second
        
    }

    return (EXIT_SUCCESS);
}

