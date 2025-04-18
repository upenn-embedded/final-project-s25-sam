/* 
 * File:   main.c
 * Author: saanvimmehta
 *
 * Created on April 7, 2025, 12:50 PM
 */

// ultrasonic sensor - start after initial pressure is detected - sense very what rate are we sensing? - print first to define threshold__ - ADC __ - sense through GPIO pin (one not 2 for echo and trig to share)
// imu set up - start sensing after initial pressure is detected - ISR not polling - ___
// LCD displays set up
// buzzer set up (set up timers) PWM
// timers for sensing
// timers for ISRs
// pressure sensors everything else depends on 
// ES32 App for monitoring progress over time 

// before main define sensing 
// before main define ISRs for remaining peripheral sensing 
// define good v.s. bad posture
// trigger lCD and Buzzer responses based on detected events
// main begin and run sensing 

#define F_CPU 16000000UL  // ? Set CPU frequency to 16 MHz
#include <util/delay.h>   // Delay utilities


// === AVR Libraries ===
#include <avr/io.h>        // Standard I/O definitions for AVR
#include <avr/interrupt.h> // Interrupts
#include <avr/sleep.h>     // Sleep modes (not used here, but included)
#include <stdlib.h>        // General utilities
#include <stdio.h>         // Standard I/O (e.g., printf)

// UART library (custom or provided) for serial communication
#include "uart.h"

// === Constants & Macros ===
#define BAUD 9600  // UART Baud rate
#define BAUD_PRESCALE (((F_CPU / (BAUD * 16UL))) - 1)  // ? Recalculates correctly for 16 MHz
#define TRIG_PIN PB1
#define ECHO_PIN PB0  // must be ICP1 for Timer1 input capture to work
#define THRESHOLD 410      // Pressure sensor threshold to detect presence

//// === LCD Pin Definitions ===
//#define LCD_RS PC4
//#define LCD_EN PC5
//#define LCD_RS_PORT PORTC
//#define LCD_EN_PORT PORTC
//#define LCD_RS_DDR  DDRC
//#define LCD_EN_DDR  DDRC
//
//
//// === LCD Port Mappings ===
//#define LCD_RS_PORT PORTB
//#define LCD_EN_PORT PORTB
//#define LCD_DATA_PORTB PORTB
//#define LCD_DATA_PORTD PORTD
//
//#define LCD_RS_DDR  DDRB
//#define LCD_EN_DDR  DDRB
//#define LCD_DATA_DDRB DDRB
//#define LCD_DATA_DDRD DDRD

// === Global Flags ===
volatile uint8_t low_pressure_count = 0;  // Count of consecutive low pressure readings
volatile uint8_t peripherals_ready = 0;   // Flag indicating peripherals should start sensing

//// === LCD Utility Functions ===
//
//// Pulse the EN line to "latch in" data
//void lcd_enable_pulse() {
//    LCD_EN_PORT |= (1 << LCD_EN);
//    _delay_us(1);
//    LCD_EN_PORT &= ~(1 << LCD_EN);
//    _delay_us(100);
//}
//
//// Send 4 bits to LCD
//void lcd_send_nibble(uint8_t nibble) {
//    if (nibble & 0x01) LCD_DATA_PORTB |= (1 << LCD_D4); else LCD_DATA_PORTB &= ~(1 << LCD_D4);
//    if (nibble & 0x02) LCD_DATA_PORTB |= (1 << LCD_D5); else LCD_DATA_PORTB &= ~(1 << LCD_D5);
//    if (nibble & 0x04) LCD_DATA_PORTB |= (1 << LCD_D6); else LCD_DATA_PORTB &= ~(1 << LCD_D6);
//    if (nibble & 0x08) LCD_DATA_PORTD |= (1 << LCD_D7); else LCD_DATA_PORTD &= ~(1 << LCD_D7);
//    lcd_enable_pulse();
//}
//
//// Send full byte (split into two nibbles)
//void lcd_send_byte(uint8_t byte, uint8_t is_data) {
//    if (is_data) LCD_RS_PORT |= (1 << LCD_RS);
//    else LCD_RS_PORT &= ~(1 << LCD_RS);
//
//    lcd_send_nibble(byte >> 4);
//    lcd_send_nibble(byte & 0x0F);
//    _delay_ms(2);
//}
//
//void lcd_command(uint8_t cmd) { lcd_send_byte(cmd, 0); }  // Command mode
//void lcd_write_char(char c) { lcd_send_byte(c, 1); }      // Data mode
//void lcd_write_string(const char *str) { while (*str) lcd_write_char(*str++); }  // String print
//
//// Initialize LCD display
//void lcd_init() {
//    LCD_RS_DDR |= (1 << LCD_RS);
//    LCD_EN_DDR |= (1 << LCD_EN);
//    LCD_DATA_DDRB |= (1 << LCD_D4) | (1 << LCD_D5) | (1 << LCD_D6);
//    LCD_DATA_DDRD |= (1 << LCD_D7);
//
//    _delay_ms(40);
//    lcd_send_nibble(0x03); _delay_ms(5);
//    lcd_send_nibble(0x03); _delay_us(150);
//    lcd_send_nibble(0x03); _delay_us(150);
//    lcd_send_nibble(0x02);
//
//    lcd_command(0x28);  // 4-bit, 2-line, 5x8 font
//    lcd_command(0x0C);  // Display ON, cursor OFF
//    lcd_command(0x01);  // Clear screen
//    _delay_ms(2);
//    lcd_command(0x06);  // Increment cursor
//}

// === Buzzer Setup ===
#define BUZZER_PIN PD5
#define BUZZER_DDR DDRD
#define BUZZER_PORT PORTD

// Display bad posture warning and activate buzzer
//void handle_bad_posture() {
//    lcd_command(0x01);
//    _delay_ms(2);
//    lcd_write_string("Sit up straight");
//    BUZZER_PORT |= (1 << BUZZER_PIN);
//    _delay_ms(1000);
//    BUZZER_PORT &= ~(1 << BUZZER_PIN);
//}

// === Additional Globals ===
volatile uint16_t timer_count = 0;     // Captured echo duration
volatile uint8_t measurementReady = 0; // Flag for when ultrasonic measurement is ready
volatile uint8_t sensing_enabled = 0;  // Start full sensing once initial condition is met

// === Timer1: Ultrasonic Sensor Echo Capture Setup ===
void timer1_init() {
    TCCR1A = 0;                         // Normal mode
    TCCR1B = (1 << CS11);              // Prescaler = 8
    TIMSK1 = (1 << ICIE1);             // Enable input capture interrupt
    TCCR1B |= (1 << ICES1);            // First look for rising edge
}

// === Timer2: Set for ~160ms, use ISR to count to 3s ===
void timer2_init() {
    TCCR2A = (1 << WGM21); // CTC mode
    TCCR2B = (1 << CS22);  // Prescaler = 64
    OCR2A = 155;           // 10ms: (155 + 1) * 64 / 1,000,000 = ~10ms
    TIMSK2 = (1 << OCIE2A); // Enable compare match interrupt
}


// === ADC Setup ===
void adc_init() {
    ADMUX = (1 << REFS0);  // Reference voltage = AVcc
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);  // Enable ADC with prescaler 64
}

// Read from specified ADC channel
uint16_t adc_read(uint8_t channel) {
    if (channel > 7) return 0;                      // Sanity check
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);      // Select channel
    ADCSRA |= (1 << ADSC);                          // Start conversion
    while (ADCSRA & (1 << ADSC));                   // Wait for conversion to finish
    return ADC;                                     // Return result
}

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
//     DDRB &= ~(1 << TRIG_ECHO_PIN);
 }
 
 void prepare_for_ultrasonic_measurement() {
    TIMSK1 |= (1 << ICIE1); // turn on input capture
    TCCR1B |= (1 << ICES1); // rising edge detection
    TIFR1 |= (1 << ICF1); // clear any previous interrupt flag
    sei();
 }
 

// === ISR: Ultrasonic Echo Capture ===

// // === ISR: Ultrasonic Echo ===
 static uint16_t start_time = 0;
 ISR(TIMER1_CAPT_vect) {
     if (TCCR1B & (1 << ICES1)) {
         start_time = ICR1;
         printf("Rising edge detected\n");
         TCCR1B &= ~(1 << ICES1); // switch to falling edge detection
     } else {
         timer_count = ICR1 - start_time;
         TCCR1B |= (1 << ICES1);
         measurementReady = 1;
         printf("Falling edge ");
         TIMSK1 &= ~(1 << ICIE1); // disable interrupts
     }
     TIFR1 |= (1 << ICF1); // clear
}


//ISR(TIMER1_CAPT_vect) {
//    static uint16_t start_time = 0;
//    if (TCCR1B & (1 << ICES1)) {  // Rising edge
//        start_time = ICR1;        // Capture start time
//        TCCR1B &= ~(1 << ICES1);  // Now look for falling edge
//    } else {  // Falling edge
//        timer_count = ICR1 - start_time;  // Measure pulse width
//        measurementReady = 1;             // Mark measurement complete
//        TCCR1B |= (1 << ICES1);           // Reset for rising edge
//    }
//}

volatile uint16_t tick_counter = 0;

ISR(TIMER2_COMPA_vect) {
    tick_counter++;  // Called every 10ms
    if (tick_counter >= 300) {  // 300 * 10ms = 3000ms = 3s
        tick_counter = 0;

        uint16_t s0 = adc_read(0);

        if (s0 > THRESHOLD) {
            low_pressure_count++;
        } else {
            low_pressure_count = 0;
        }

        if (low_pressure_count >= 5 && !peripherals_ready) {
            peripherals_ready = 1;
            printf("peripherals begin sensing\n");
        }
    }
}

// === Main Program ===
  int main() {
    uart_init();        // Serial print support
    adc_init();         // Set up ADC
    timer1_init();      // Ultrasonic input capture timer
    timer2_init();      // 10ms tick -> 3s ISR logic
    sei();              // Enable global interrupts
    init_ultrasonic();

    DDRC &= ~((1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3)); // PC0-PC3 as inputs
    DDRB |= (1 << TRIG_PIN);   // Set TRIG as output
    DDRB &= ~(1 << ECHO_PIN);  // Set ECHO as input
    PORTB &= ~(1 << ECHO_PIN); // No pull-up resistor


//    lcd_init();                     // Start LCD
//    lcd_write_string("Hello, world!");  // Boot message

    BUZZER_DDR |= (1 << BUZZER_PIN);    // Buzzer pin as output
    BUZZER_PORT &= ~(1 << BUZZER_PIN);  // Buzzer off

    while (1) {
        uint16_t s0 = adc_read(0);  // Read PC0
        printf("Pressure Reading (PC0): %u\n", s0);

        // Enable sensing after condition met
        if (!sensing_enabled && peripherals_ready) {
            sensing_enabled = 1;
            printf("Sensing enabled via ISR logic.\n");
        }

        if (sensing_enabled) {
            prepare_for_ultrasonic_measurement();
            send_trigger_pulse();  // Trigger ultrasonic pulse
            printf("Pulse sent.\n");

            _delay_ms(60);         // Wait for echo response

            if (measurementReady) {

                uint16_t duration_us = timer_count / 2;      // Convert to �s
                uint16_t distance_cm = duration_us / 58;     // Convert to cm
                printf("Ultrasonic Distance: %d cm\n", distance_cm);
                measurementReady = 0;
            }

            // handle_bad_posture();  // LCD + Buzzer (still commented out)
            // _delay_ms(2000);       // 2s pause between alerts
        }
    }
}

  // change rate of pressure sensing after weight is detected
  // check why ultrasonic is being 



//#define F_CPU 1000000UL
//#include <util/delay.h>
//
//#include <avr/io.h>
//#include <avr/interrupt.h>
//#include <avr/sleep.h>
//#include <stdlib.h>
//#include <stdio.h>
//
//#include "uart.h"
//
//#define BAUD 9600
//#define BAUD_PRESCALE (((F_CPU / (BAUD * 16UL))) - 1)
//#define TRIG_ECHO_PIN PB1
//#define THRESHOLD 500
//#define POSTURE_DISTANCE_THRESHOLD 25
//#define BACK_PRESSURE_THRESHOLD 300
//
//#define LCD_RS     PB0
//#define LCD_EN     PB1
//#define LCD_D4     PB2
//#define LCD_D5     PB3
//#define LCD_D6     PB5
//#define LCD_D7     PD6
//
//#define LCD_RS_PORT PORTB
//#define LCD_EN_PORT PORTB
//#define LCD_DATA_PORTB PORTB
//#define LCD_DATA_PORTD PORTD
//
//#define LCD_RS_DDR  DDRB
//#define LCD_EN_DDR  DDRB
//#define LCD_DATA_DDRB DDRB
//#define LCD_DATA_DDRD DDRD
//
//#define BUZZER_PIN PD5
//#define BUZZER_DDR DDRD
//#define BUZZER_PORT PORTD
//
//volatile uint16_t timer_count = 0;
//volatile uint8_t measurementReady = 0;
//volatile uint8_t sensing_enabled = 0;
//volatile uint8_t distance_cm = 0;
//
//void lcd_enable_pulse() {
//    LCD_EN_PORT |= (1 << LCD_EN);
//    _delay_us(1);
//    LCD_EN_PORT &= ~(1 << LCD_EN);
//    _delay_us(100);
//}
//
//void lcd_send_nibble(uint8_t nibble) {
//    if (nibble & 0x01) LCD_DATA_PORTB |= (1 << LCD_D4); else LCD_DATA_PORTB &= ~(1 << LCD_D4);
//    if (nibble & 0x02) LCD_DATA_PORTB |= (1 << LCD_D5); else LCD_DATA_PORTB &= ~(1 << LCD_D5);
//    if (nibble & 0x04) LCD_DATA_PORTB |= (1 << LCD_D6); else LCD_DATA_PORTB &= ~(1 << LCD_D6);
//    if (nibble & 0x08) LCD_DATA_PORTD |= (1 << LCD_D7); else LCD_DATA_PORTD &= ~(1 << LCD_D7);
//    lcd_enable_pulse();
//}
//
//void lcd_send_byte(uint8_t byte, uint8_t is_data) {
//    if (is_data) LCD_RS_PORT |= (1 << LCD_RS);
//    else LCD_RS_PORT &= ~(1 << LCD_RS);
//    lcd_send_nibble(byte >> 4);
//    lcd_send_nibble(byte & 0x0F);
//    _delay_ms(2);
//}
//
//void lcd_command(uint8_t cmd) { lcd_send_byte(cmd, 0); }
//void lcd_write_char(char c) { lcd_send_byte(c, 1); }
//void lcd_write_string(const char *str) { while (*str) lcd_write_char(*str++); }
//
//void lcd_init() {
//    LCD_RS_DDR |= (1 << LCD_RS);
//    LCD_EN_DDR |= (1 << LCD_EN);
//    LCD_DATA_DDRB |= (1 << LCD_D4) | (1 << LCD_D5) | (1 << LCD_D6);
//    LCD_DATA_DDRD |= (1 << LCD_D7);
//    _delay_ms(40);
//    lcd_send_nibble(0x03); _delay_ms(5);
//    lcd_send_nibble(0x03); _delay_us(150);
//    lcd_send_nibble(0x03); _delay_us(150);
//    lcd_send_nibble(0x02);
//    lcd_command(0x28); lcd_command(0x0C); lcd_command(0x01); _delay_ms(2); lcd_command(0x06);
//}
//
//void handle_bad_posture() {
//    lcd_command(0x01);
//    _delay_ms(2);
//    lcd_write_string("Sit up straight");
//    BUZZER_PORT |= (1 << BUZZER_PIN);
//    _delay_ms(1000);
//    BUZZER_PORT &= ~(1 << BUZZER_PIN);
//}
//
//void timer1_init() {
//    TCCR1A = 0;
//    TCCR1B = (1 << CS11);
//    TIMSK1 = (1 << ICIE1);
//    TCCR1B |= (1 << ICES1);
//}
//
//void timer2_init() {
//    TCCR2A = (1 << WGM21);
//    TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20);
//    OCR2A = 156;
//    TIMSK2 = (1 << OCIE2A);
//}
//
//void adc_init() {
//    ADMUX = (1 << REFS0);
//    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);
//}
//
//uint16_t adc_read(uint8_t channel) {
//    if (channel > 7) return 0;
//    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
//    ADCSRA |= (1 << ADSC);
//    while (ADCSRA & (1 << ADSC));
//    return ADC;
//}
//
//void send_trigger_pulse() {
//    DDRB |= (1 << TRIG_ECHO_PIN);
//    PORTB &= ~(1 << TRIG_ECHO_PIN);
//    _delay_us(2);
//    PORTB |= (1 << TRIG_ECHO_PIN);
//    _delay_us(10);
//    PORTB &= ~(1 << TRIG_ECHO_PIN);
//    DDRB &= ~(1 << TRIG_ECHO_PIN);
//}
//
//ISR(TIMER1_CAPT_vect) {
//    static uint16_t start_time = 0;
//    if (TCCR1B & (1 << ICES1)) {
//        start_time = ICR1;
//        TCCR1B &= ~(1 << ICES1);
//    } else {
//        timer_count = ICR1 - start_time;
//        distance_cm = (timer_count / 2) / 58;
//        measurementReady = 1;
//        TCCR1B |= (1 << ICES1);
//    }
//}
//
//ISR(TIMER2_COMPA_vect) {
//    static uint16_t tick_counter = 0;
//    tick_counter++;
//    if (tick_counter >= 200) {
//        tick_counter = 0;
//        if (!sensing_enabled) {
//            uint16_t s0 = adc_read(0);
//            uint16_t s1 = adc_read(1);
//            if (s0 > THRESHOLD && s1 > THRESHOLD) sensing_enabled = 1;
//        } else {
//            uint16_t s2 = adc_read(2);
//            uint16_t s3 = adc_read(3);
//            if (distance_cm < POSTURE_DISTANCE_THRESHOLD || s2 < BACK_PRESSURE_THRESHOLD || s3 < BACK_PRESSURE_THRESHOLD) {
//                handle_bad_posture();
//            }
//        }
//    }
//}
//
//int main() {
//    uart_init();
//    adc_init();
//    timer1_init();
//    timer2_init();
//    sei();
//
//    DDRC &= ~((1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3));
//    DDRB &= ~(1 << TRIG_ECHO_PIN);
//    BUZZER_DDR |= (1 << BUZZER_PIN);
//    BUZZER_PORT &= ~(1 << BUZZER_PIN);
//
//    lcd_init();
//    lcd_write_string("Hello, world!");
//
//    while (1) {
//        if (sensing_enabled) {
//            send_trigger_pulse();
//            _delay_ms(60);
//        }
//    }
//}
//// // === Microcontroller Clock Definition ===
//// #define F_CPU 1000000UL  // Set CPU frequency to 1 MHz for delay functions
//// #include <util/delay.h>
//
//// // === AVR Libraries ===
//// #include <avr/io.h>
//// #include <avr/interrupt.h>
//// #include <avr/sleep.h>
//// #include <stdlib.h>
//// #include <stdio.h>
//
//// // === Optional FreeRTOS Includes (commented out) ===
//// // #include "FreeRTOS.h"
// // #include "FreeRTOSConfig.h"
// // #include "task.h"
// // #include "queue.h"
// // #include "semphr.h"

// #include "uart.h"  // UART communication functions

// // === Constants & Macros ===
// #define BAUD 9600
// #define BAUD_PRESCALE (((F_CPU / (BAUD * 16UL))) - 1)  // Baud rate calculation for UART
// #define TRIG_ECHO_PIN PB1  // Pin used for both triggering and receiving ultrasonic signal
// #define THRESHOLD 500      // Pressure sensor threshold

// // === LCD Pin Configuration ===
// #define LCD_RS     PB0
// #define LCD_EN     PB1
// #define LCD_D4     PB2
// #define LCD_D5     PB3
// #define LCD_D6     PB5
// #define LCD_D7     PD6

// // === LCD Ports and DDRs ===
// #define LCD_RS_PORT PORTB
// #define LCD_EN_PORT PORTB
// #define LCD_DATA_PORTB PORTB
// #define LCD_DATA_PORTD PORTD

// #define LCD_RS_DDR  DDRB
// #define LCD_EN_DDR  DDRB
// #define LCD_DATA_DDRB DDRB
// #define LCD_DATA_DDRD DDRD

// // === LCD Utility Functions ===
// void lcd_enable_pulse() {
//     LCD_EN_PORT |= (1 << LCD_EN);
//     _delay_us(1);
//     LCD_EN_PORT &= ~(1 << LCD_EN);
//     _delay_us(100);
// }

// void lcd_send_nibble(uint8_t nibble) {
//     if (nibble & 0x01) LCD_DATA_PORTB |= (1 << LCD_D4); else LCD_DATA_PORTB &= ~(1 << LCD_D4);
//     if (nibble & 0x02) LCD_DATA_PORTB |= (1 << LCD_D5); else LCD_DATA_PORTB &= ~(1 << LCD_D5);
//     if (nibble & 0x04) LCD_DATA_PORTB |= (1 << LCD_D6); else LCD_DATA_PORTB &= ~(1 << LCD_D6);
//     if (nibble & 0x08) LCD_DATA_PORTD |= (1 << LCD_D7); else LCD_DATA_PORTD &= ~(1 << LCD_D7);
//     lcd_enable_pulse();
// }

// void lcd_send_byte(uint8_t byte, uint8_t is_data) {
//     if (is_data) LCD_RS_PORT |= (1 << LCD_RS);
//     else LCD_RS_PORT &= ~(1 << LCD_RS);

//     lcd_send_nibble(byte >> 4);
//     lcd_send_nibble(byte & 0x0F);
//     _delay_ms(2);
// }

// void lcd_command(uint8_t cmd) {
//     lcd_send_byte(cmd, 0);
// }

// void lcd_write_char(char c) {
//     lcd_send_byte(c, 1);
// }

// void lcd_write_string(const char *str) {
//     while (*str) lcd_write_char(*str++);
// }

// void lcd_init() {
//     LCD_RS_DDR |= (1 << LCD_RS);
//     LCD_EN_DDR |= (1 << LCD_EN);
//     LCD_DATA_DDRB |= (1 << LCD_D4) | (1 << LCD_D5) | (1 << LCD_D6);
//     LCD_DATA_DDRD |= (1 << LCD_D7);

//     _delay_ms(40);

//     lcd_send_nibble(0x03); _delay_ms(5);
//     lcd_send_nibble(0x03); _delay_us(150);
//     lcd_send_nibble(0x03); _delay_us(150);
//     lcd_send_nibble(0x02);

//     lcd_command(0x28);
//     lcd_command(0x0C);
//     lcd_command(0x01);
//     _delay_ms(2);
//     lcd_command(0x06);
// }

// // === Buzzer Configuration ===
// #define BUZZER_PIN PD5
// #define BUZZER_DDR DDRD
// #define BUZZER_PORT PORTD

// // === Alert Handler ===
// void handle_bad_posture() {
//     lcd_command(0x01);
//     _delay_ms(2);
//     lcd_write_string("Sit up straight");
//     BUZZER_PORT |= (1 << BUZZER_PIN);
//     _delay_ms(1000);
//     BUZZER_PORT &= ~(1 << BUZZER_PIN);
// }

// // === Global Flags and Counters ===
// volatile uint16_t timer_count = 0;
// volatile uint8_t measurementReady = 0;
// volatile uint8_t sensing_enabled = 0;

// // === Timer1: Ultrasonic echo capture ===
// void timer1_init() {
//     TCCR1A = 0;
//     TCCR1B = (1 << CS11);
//     TIMSK1 = (1 << ICIE1);
//     TCCR1B |= (1 << ICES1);
// }

// // === Timer2: ~10ms tick for 2s logging loop ===
// void timer2_init() {
//     TCCR2A = (1 << WGM21);
//     TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20);
//     OCR2A = 156;
//     TIMSK2 = (1 << OCIE2A);
// }

// // === ADC Initialization ===
// void adc_init() {
//     ADMUX = (1 << REFS0);
//     ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);
// }

// // === ADC Read ===
// uint16_t adc_read(uint8_t channel) {
//     if (channel > 7) return 0;
//     ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
//     ADCSRA |= (1 << ADSC);
//     while (ADCSRA & (1 << ADSC));
//     return ADC;
// }

// // === Ultrasonic Trigger Pulse ===
// void send_trigger_pulse() {
//     DDRB |= (1 << TRIG_ECHO_PIN);
//     PORTB &= ~(1 << TRIG_ECHO_PIN); _delay_us(2);
//     PORTB |= (1 << TRIG_ECHO_PIN); _delay_us(10);
//     PORTB &= ~(1 << TRIG_ECHO_PIN);
//     DDRB &= ~(1 << TRIG_ECHO_PIN);
// }

// // === ISR: Ultrasonic Echo ===
// ISR(TIMER1_CAPT_vect) {
//     static uint16_t start_time = 0;
//     if (TCCR1B & (1 << ICES1)) {
//         start_time = ICR1;
//         TCCR1B &= ~(1 << ICES1);
//     } else {
//         timer_count = ICR1 - start_time;
//         measurementReady = 1;
//         TCCR1B |= (1 << ICES1);
//     }
// }

// // === ISR: 2s Sensor Logging ===
// ISR(TIMER2_COMPA_vect) {
//     if (!sensing_enabled) return;

//     static uint16_t tick_counter = 0;
//     tick_counter++;

//     if (tick_counter >= 200) {
//         tick_counter = 0;
//         uint16_t s2 = adc_read(2);
//         uint16_t s3 = adc_read(3);
//         printf("PC2 (ADC2): %u\tPC3 (ADC3): %u\n", s2, s3);
//     }
// }

// // === Main Function ===
// int main() {
//     uart_init();
//     adc_init();
//     timer1_init();
//     timer2_init();
//     sei();

//     DDRC &= ~((1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3));
//     DDRB &= ~(1 << TRIG_ECHO_PIN);

//     uint16_t loop_counter = 0;

//     lcd_init();
//     lcd_write_string("Hello, world!");

//     BUZZER_DDR |= (1 << BUZZER_PIN);
//     BUZZER_PORT &= ~(1 << BUZZER_PIN);

//     while (1) {
//         if (!sensing_enabled && ++loop_counter >= 50) {
//             loop_counter = 0;
//             uint16_t s0 = adc_read(0);
//             uint16_t s1 = adc_read(1);
//             printf("PC0 (ADC0): %u\tPC1 (ADC1): %u\n", s0, s1);

//             if (s0 > THRESHOLD && s1 > THRESHOLD) {
//                 sensing_enabled = 1;
//                 printf("Initial pressure detected ? enabling sensors\n");
//             }
//         }

//         if (sensing_enabled) {
//             send_trigger_pulse();
//             _delay_ms(60);

//             if (measurementReady) {
//                 measurementReady = 0;
//                 uint16_t duration_us = timer_count / 2;
//                 uint16_t distance_cm = duration_us / 58;
//                 printf("Ultrasonic Distance: %d cm\n", distance_cm);
//             }
//         }

//         if (sensing_enabled) {
//             handle_bad_posture();
//             _delay_ms(2000);
//         }
//     }
// }


// old code one pin that builds
/*
#include <stdio.h>
#include <stdlib.h>

don't start peripheral sensing till first two pressure sensors (p_- & p __ sense weight (past a specific threshold)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "uart.h"

// Define clock frequency (/w 16MHz clock)
# define F_CPU 1000000UL
#define BAUD 9600
#define BAUD_PRESCALE (((F_CPU / (BAUD * 16UL))) - 1)

#define TRIG_PIN PB1
#define ECHO_PIN PB0

volatile uint16_t timer_count = 0;
volatile uint8_t measurementReady = 0;

// Initialize Timer1 in normal mode with 1µs resolution
void timer1_init() {
    TCCR1A = 0;
    TCCR1B = (1 << CS11);  // Prescaler = 8 (1 tick = 0.5 µs at 16MHz)
    TIMSK1 = (1 << ICIE1); // Enable input capture interrupt
    //Initialize abc
    TCCR1B |= (1 << ICES1); // Start with Rising Edge
}

// Send 10µs pulse on TRIG_PIN
void send_trigger_pulse() {
    DDRB |= (1 << TRIG_PIN);  // Set TRIG_PIN as output
    PORTB &= ~(1 << TRIG_PIN); // Ensure it's LOW
    _delay_us(2);
    PORTB |= (1 << TRIG_PIN);  // Set HIGH for 10µs
    _delay_us(10);
    PORTB &= ~(1 << TRIG_PIN); // Set LOW again
}

// ISR for input capture on ECHO_PIN (/w Edge Handling)
ISR(TIMER1_CAPT_vect) {
    static uint16_t start_time = 0;

    if (TCCR1B & (1 << ICES1)) {  // Rising edge detected
        start_time = ICR1;  // Store start time
        TCCR1B &= ~(1 << ICES1);  // Switch to falling edge detection
         //  Compute Distance Outside ISR
            uint16_t duration = timer_count / 2; // Convert to µs (each tick = 0.5µs)
            uint16_t distance = duration / 58;  // Convert to cm
            printf("Distance: ");
            printf("%d", distance);
            printf(" cm\n");
            
    } else {  // Falling edge detected
        timer_count = ICR1 - start_time;  // Compute pulse duration
        measurementReady = 1;
        TCCR1B |= (1 << ICES1);  // Switch back to rising edge detection
    }
}

int main() {
    uart_init();
    timer1_init();
    sei();  // Enable global interrupts

    DDRB &= ~(1 << ECHO_PIN); // Set ECHO_PIN as input
    DDRB |= (1 << TRIG_PIN);  // Set TRIG_PIN as output

    while (1) {
        send_trigger_pulse();
        _delay_ms(60);  // Wait before next trigger (ensures echo has returned)
    }
}
*/