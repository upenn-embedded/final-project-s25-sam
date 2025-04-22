/*
 * File:   main.c
 * Author: saanvimmehta
 *
 * Created on April 7, 2025, 12:50 PM
 */

#define F_CPU 16000000UL   // ? Set CPU frequency to 16 MHz
#include <util/delay.h>    // Delay utilities


#include "LCD_GFX.h"
#include "ST7735.h"

// === AVR Libraries ===
#include <avr/interrupt.h>   // Interrupts
#include <avr/io.h>          // Standard I/O definitions for AVR
#include <avr/sleep.h>       // Sleep modes (not used here, but included)
#include <stdio.h>           // Standard I/O (e.g., printf)
#include <stdlib.h>          // General utilities

// UART library (custom or provided) for serial communication
#include "drv2605.h"
#include "i2c.h"
#include "uart.h"

// === Constants & Macros ===
#define BAUD                  9600                              // UART Baud rate
#define BAUD_PRESCALE         (((F_CPU / (BAUD * 16UL))) - 1)   // ? Recalculates correctly for 16 MHz
#define TRIG_PIN              PE2
#define ECHO_PIN              PE3   // must be ICP1 for Timer1 input capture to work
#define THRESHOLD             410   // Pressure sensor threshold to detect presence
#define DISTANCE_CM_THRESHOLD 20

// === Global Flags ===
volatile uint8_t low_pressure_count = 0;   // Count of consecutive low pressure readings. Low pressure values mean that the user is sitting on the cushion.
volatile uint8_t high_pressure_count = 0; // Count of consecutive high pressure readings. High pressure values mean that the user is not sitting on the cushion.
volatile uint8_t sensing_enabled = 0;      // Flag indicating that the peripherals should start sensing.

// === Buzzer Setup ===
#define BUZZER_PIN  PD5
#define BUZZER_DDR  DDRD
#define BUZZER_PORT PORTD

// === Additional Globals ===
volatile uint16_t timer_count = 0;       // Captured echo duration

// === Timer1: Ultrasonic Sensor Echo Capture Setup ===
void
timer1_init() {
    TCCR1A = 0;               // Normal mode
    TCCR1B = (1 << CS11);     // Prescaler = 8
    TIMSK1 = (1 << ICIE1);    // Enable input capture interrupt
    TCCR1B |= (1 << ICES1);   // First look for rising edge
}

// === Timer2: Set for ~160ms, use ISR to count to 3s ===
void
timer2_init() {
    TCCR2A = (1 << WGM21);    // CTC mode
    TCCR2B = (1 << CS22);     // Prescaler = 64
    OCR2A = 155;              // 10ms: (155 + 1) * 64 / 1,000,000 = ~10ms
    TIMSK2 = (1 << OCIE2A);   // Enable compare match interrupt
}

// === ADC Setup ===
void
adc_init() {
    ADMUX = (1 << REFS0);                                 // Reference voltage = AVcc
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);   // Enable ADC with prescaler 64
}

// Read from specified ADC channel
uint16_t
adc_read(uint8_t channel) {
    if (channel > 7)
        return 0;                                // Sanity check
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);   // Select channel
    ADCSRA |= (1 << ADSC);                       // Start conversion
    while (ADCSRA & (1 << ADSC))
        ;         // Wait for conversion to finish
    return ADC;   // Return result
}

void
init_ultrasonic() {
    // Timer1, prescale 64
    TCCR3B |= (1 << CS11);
    TCCR3B |= (1 << CS10);
    
    // Set Timer 3 to Normal
    TCCR3A &= ~(1 << WGM30);
    TCCR3A &= ~(1 << WGM31);
    TCCR3B &= ~(1 << WGM32);
    
    DDRD |= (1 << PD3); // set PD3 as output (trig)
    DDRE &= ~(1 << PE2); // set PE2 as input (echo)
    
    TIFR3 |= (1 << ICF3); // clear input capture flag
}

void
send_trigger_pulse() {
    DDRE |= (1 << TRIG_PIN);
    PORTE |= (1 << TRIG_PIN);
    _delay_us(10);
    PORTE &= ~(1 << TRIG_PIN);
    DDRE &= ~(1 << TRIG_PIN);
}

void
prepare_for_ultrasonic_measurement() {
    TIMSK3 |= (1 << ICIE3);   // turn on input capture
    TCCR3B |= (1 << ICES3);   // rising edge detection
    TIFR3 |= (1 << ICF3);     // clear any previous interrupt flag
    sei();
}


uint8_t looking_for_rising;
uint8_t distance_read;
ISR(TIMER3_CAPT_vect) {
    if (looking_for_rising) {
        TCNT3 = 0; // reset timer
        TCCR3B &= ~(1 << ICES3); // switch to falling edge detection
        looking_for_rising = 0;
    } 
    else { // looking for echo falling edge  
        TIMSK3 &= ~(1 << ICIE3); // disable input capture interrupt
        timer_count = ICR3; // time of echo pulse
        TCCR3B |= (1 << ICES3); // look for rising edge
        looking_for_rising = 1;
        distance_read = 1;
    }
    
    TIFR3 |= (1 << ICF3); // clear input capture flag
}

uint16_t echo_to_cm(uint16_t echo_ticks) {
    // echo_time is in ticks
    // 16 MHz / 64 = 250000 Hz
    // 0.000004 seconds per tick
    // one microsecond is 0.25 ticks
    // one tick is 4 uS
    
    int uS = echo_ticks * 4;
    int cm = uS / 58;
    return cm;
}

// ISR(TIMER1_CAPT_vect) {
//     static uint16_t start_time = 0;
//     if (TCCR1B & (1 << ICES1)) {  // Rising edge
//         start_time = ICR1;        // Capture start time
//         TCCR1B &= ~(1 << ICES1);  // Now look for falling edge
//     } else {  // Falling edge
//         timer_count = ICR1 - start_time;  // Measure pulse width
//         measurementReady = 1;             // Mark measurement complete
//         TCCR1B |= (1 << ICES1);           // Reset for rising edge
//     }
// }

volatile uint16_t tick_counter = 0; // each tick is 10ms


uint16_t s0_threshold = 500;
uint16_t s1_threshold = 500;
uint16_t s2_threshold = 500;
uint16_t s3_threshold = 500;
void
init_pressure_thresholds() {
    uint32_t totals[4] = {0};
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 4; j++) {
            totals[j] += adc_read(j);
        }
        _delay_ms(100);
    }

    for (int j = 0; j < 4; j++) {
        totals[j] /= 100;
        totals[j] += 50;
    }

    s0_threshold = totals[0] + 50; // This sensor is on the seat, so it should experience more pressure to turn on
    s1_threshold = totals[1];
    s2_threshold = totals[2];
    s3_threshold = totals[3];
}

ISR(TIMER2_COMPA_vect) {
    tick_counter++;              // Called every 10ms
    if (tick_counter >= 300) {   // 300 * 10ms = 3000ms = 3s
        tick_counter = 0;
        uint16_t s0 = adc_read(0);

        if (!sensing_enabled) {
            if (s0 > s0_threshold) {
                low_pressure_count++;
            } else {
                low_pressure_count = 0;
            }

            if (low_pressure_count >= 5) {
                printf("peripherals begin sensing\n");
                sensing_enabled = 1;
            }
        } else {
            if (s0 < s0_threshold) {
                high_pressure_count++;
            } else {
                high_pressure_count = 0;
            }

            if (high_pressure_count >= 20) {
                printf("peripherals stop sensing\n");
                sensing_enabled = 0;
            }
        }
    }
}

// === Main Program ===
int
main() {
    uart_init();     // Serial print support
    adc_init();      // Set up ADC
    timer1_init();   // Ultrasonic input capture timer
    timer2_init();   // 10ms tick -> 3s ISR logic
    init_ultrasonic();
    sei();           // Enable global interrupts
    i2c_init();
    // drv2605_init();
    init_pressure_thresholds();   // this takes some time

    printf("Thresholds: %u %u %u %u\n", s0_threshold, s1_threshold, s2_threshold, s3_threshold);
    
//    lcd_init();                          // Start LCD
//    LCD_setScreen(WHITE);
//    LCD_drawString(10, 30, "Sit up straight", BLACK, WHITE);

    BUZZER_DDR |= (1 << BUZZER_PIN);     // Buzzer pin as output
    BUZZER_PORT &= ~(1 << BUZZER_PIN);   // Buzzer off

    while (1) {
        if (sensing_enabled) {
            
            looking_for_rising = 1;
            TIMSK3 |= (1 << ICIE3); // enable input capture interrupt
            TCCR3B |= (1 << ICES3); // look for rising edge

            // 10 uS pulse
            PORTD |= (1 << PD3);
            _delay_us(10);
            PORTD &= ~(1 << PD3);

            printf("busy waiting\n");
            
            _delay_ms(60);
            
            uint16_t distance_cm = 0;
            if (distance_read) {
                printf("timer_count %u\n", timer_count);
                distance_cm = (uint16_t) echo_to_cm(timer_count);
            }
            distance_read = 0;

            // _delay_ms(2000);       // 2s pause between alerts

            // read the other 3 pressure sensors
            uint16_t s1 = adc_read(1);   // PC1
            uint16_t s2 = adc_read(2);   // PC2
            uint16_t s3 = adc_read(3);   // PC3

            printf("s1 %u, s2 %u, s3 %u, %u distance_cm %u", s1, s2, s3, timer_count, distance_cm);

            if (s1 < s1_threshold || s2 < s2_threshold || s3 < s3_threshold) { //   distance_cm > DISTANCE_CM_THRESHOLD
//                drv2605_write_register_8(DRV2605_REG_WAVESEQ1, 0x01);
//                drv2605_write_register_8(DRV2605_REG_GO, 0x01);
            }
        }
    }
}