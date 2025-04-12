/* 
 * File:   newmain.c
 * Author: aagam
 *
 * Created on April 11, 2025, 9:18 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>
#include "uart.h"

// the last bit 0
#define IMU_I2C_ADDR_0 0b1101010
#define IMU_I2C_ADDR_1 0b1101011

#define TWSR_BIT_MASK 0xF8
#define MT_SLA_ACK 0x18
#define MT_SLA_NACK 0x20
#define MT_DATA_ACK 0x28
#define MT_DATA_NACK 0x30
#define MR_SLA_ACK 0x40
#define MR_SLA_NACK 0x48
#define MR_DATA_ACK 0x50
#define MR_DATA_NACK 0x58
#define N_RETRANSMIT_BEFORE_ERR 5
#define START 0b10100100
#define START_DONE 0x08

void i2c_init() {
    sei();
    
    // enable 2-wire on TWI1 (PE0 and PE1)
    TWCR1 |= (1 << TWEN);
}

int i2c_send(uint8_t addr, uint8_t* data, int n) {
    // write the data to the transmission buffer
    
    // start the two wire 
            
    // TWEN, TWSTA, TWINT must be on to start
    // note TWEN = 2
    // TWSTA = 5
    // TWINT = 7
    // so the overall bit string is 0b1x10x10x
    // noting that the 0 values help signal this is
    // a master transmitter setup
    TWCR1 = START;
    
    while (!(TWCR1 & 1 << TWINT));
    
    if ((TWSR1 & TWSR_BIT_MASK) != START_DONE) {
        return -1;
    }
    
    // retransmit
    bool ok = false;
    for (int i = 0; i < N_RETRANSMIT_BEFORE_ERR; i++) {
        TWDR1 = (addr << 1) | 0b1; // write 
        // clear the TWINT bit to start the transmission (note: clearing it means setting it to 1, which is 
        // a little counterintuitive)
        TWCR1 = (1 << TWINT) | (1 << TWEN);

        // interrupt flag is 
        while (!(TWCR1 & (1<<TWINT)));
        
        // Wait for an ack
        if ((TWSR1 & TWSR_BIT_MASK) == MT_SLA_ACK) {
            ok = true;
            break;
        }
    }
    if (!ok) {
        return -1;
    }
    
    // try to transmit data
    ok = false;
    for (int i = 0; i < n; i++) {
        TWDR1 = data[i];
        TWCR1 = (1 << TWINT) | (1 << TWEN);
        while (!(TWCR1 & (1 << TWINT)));
        
        if ((TWSR1 & TWSR_BIT_MASK) == MT_DATA_ACK) {
            ok = true;
            break;
        }
    }
    
    if (!ok) {
        return -1;
    }
    
    // stop transmission
    TWCR1 = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

void i2c_recieve(uint8_t addr, uint8_t* data, int n) {
    // set 0b1x10x10x
    TWCR1 = START;
    
    while (!(TWCR1 & 1 << TWINT));
    
    if ((TWSR1 & TWSR_BIT_MASK) != START_DONE) {
        return -1;
    }
    
    bool ok = false;
    for (int i = 0; i < N_RETRANSMIT_BEFORE_ERR; i++) {
        // clear the TWINT bit to start the transmission (note: clearing it means setting it to 1, which is 
        // a little counterintuitive)
        TWDR1 = addr << 1 & ~(0b1);
        TWCR1 = (1 << TWINT) | (1 << TWEN);
        while (!(TWCR1 & (1<<TWINT)));

        if ((TWSR1 & TWSR_BIT_MASK) == ) {
            ok = true;
            break;
        }
    }
    if (!ok) {
        return -1;
    }
    
    ok = false;
    for (int i = 0; i < n; i++) {
        TWDR1 = data[i];
        TWCR1 = (1 << TWINT) | (1 << TWEN);
        while (!(TWCR1 & (1 << TWINT)));
        
        if ((TWSR1 & TWSR_BIT_MASK) == MT_SLA_ACK) {
            ok = true;
            data[i] = TWDR1;
            break;
        }
    }
    
    if (!ok) {
        return -1;
    }
    
    // stop transmission
    TWCR1 = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

/*
 * 
 */
int main(int argc, char** argv) {
    // transmit to this peripheral
    char* data = "hello world!";
    i2c_send(IMU_I2C_ADDR_0, data, 13); // also write the null terminator just for fun
    i2c_recieve(IMU_I2C_ADDR_0, data, 13); // expect to read things back
    return (EXIT_SUCCESS);
}

   
