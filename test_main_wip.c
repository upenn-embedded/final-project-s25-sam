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

#include "drv2605.h"
#include "i2c.h"
#include "lsm6ds0.h"
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
volatile uint8_t bad_posture = 1;

// === Buzzer Setup ===
#define BUZZER_PIN  PD5
#define BUZZER_DDR  DDRD
#define BUZZER_PORT PORTD

// === Additional Globals ===
volatile uint16_t timer_count = 0;       // Captured echo duration

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

// === Ultrasonic ===
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

// === Pressure ===
volatile uint16_t tick_counter = 0; // each tick is 10ms


uint16_t s0_threshold = 500;
uint16_t s1_threshold = 500;
uint16_t s2_threshold = 500;
uint16_t s3_threshold = 500;
void
set_pressure_gyroscope_baselines() {
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
    // delay for 10 seconds to give us a chance to connect the serial monitor
    uart_init();     // Serial print support
//    _delay_ms(10000);
    
    // turn on the builtin led
    DDRB |= (1 << PB5);
    PORTB |= (1 << PB5);
    
    printf("Setting up LCDs\r\n");
//    lcd_init(); 
//    LCD_setScreen(BLACK);
//    LCD_drawString(10, 30, "Initializing...", WHITE, BLACK);
//    printf("Initializing\r\n");
//    
//    adc_init();      // Set up ADC
//    timer2_init();   // 10ms tick -> 3s ISR logic
//    init_ultrasonic();
//    i2c_init();
//    drv2605_init();
//    lsm6ds0_init();
//
//    set_pressure_gyroscope_baselines(); // This takes 10 seconds
//    LCD_drawString(10, 30, "Not sitting", WHITE, BLACK);
//
//    printf("Thresholds: %u %u %u %u\n", s0_threshold, s1_threshold, s2_threshold, s3_threshold);
//    
//    sei();           // Enable global interrupts
//
//    BUZZER_DDR |= (1 << BUZZER_PIN);     // Buzzer pin as output
//    BUZZER_PORT &= ~(1 << BUZZER_PIN);   // Buzzer off
//
//    while (1) {
//        if (sensing_enabled) {
//            LCD_drawString(10, 30, "Good posture!", WHITE, BLACK);
//            
//            looking_for_rising = 1;
//            TIMSK3 |= (1 << ICIE3); // enable input capture interrupt
//            TCCR3B |= (1 << ICES3); // look for rising edge
//
//            // 10 uS pulse
//            PORTD |= (1 << PD3);
//            _delay_us(10);
//            PORTD &= ~(1 << PD3);
//
//            printf("busy waiting\n");
//            
//            _delay_ms(60);
//            
//            uint16_t distance_cm = 0;
//            if (distance_read) {
//                printf("timer_count %u\n", timer_count);
//                distance_cm = (uint16_t) echo_to_cm(timer_count);
//            }
//            distance_read = 0;
//
//            // read the other 3 pressure sensors
//            uint16_t s1 = adc_read(1);   // PC1
//            uint16_t s2 = adc_read(2);   // PC2
//            uint16_t s3 = adc_read(3);   // PC3
//
//            // read the accelerometer
//            uint8_t x = lsm6ds0_read_register_8(LSM6DSO_OUTX_L_G, 0x00);
//            uint8_t y = lsm6ds0_read_register_8(LSM6DSO_OUTY_L_G, 0x00);
//            uint8_t z = lsm6ds0_read_register_8(LSM6DSO_OUTZ_L_G, 0x00);
//
//            printf("s1 %u, s2 %u, s3 %u, x %u, y %u, z %u, distance_cm %u", s1, s2, s3, x, y, z, distance_cm);
//
//            if (s1 < s1_threshold || s2 < s2_threshold || s3 < s3_threshold) { //   distance_cm > DISTANCE_CM_THRESHOLD
//               drv2605_write_register_8(DRV2605_REG_WAVESEQ1, 0x01);
//               drv2605_write_register_8(DRV2605_REG_GO, 0x01);
//            }
//        }
//        
//        if (bad_posture) {
//            LCD_setScreen(RED);
//            LCD_drawString(10, 30, "Bad posture! Sit up straight!", WHITE, RED);
//        }
//    }
}