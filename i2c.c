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
#include "i2c.h"


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

// See ATMega328pb datasheet 26.9.5
// This value is written to the TWCR1 register
// bit 7 (TWINT) is set 1 meaning TWINT is cleared (TWINT is set when 0 and cleared when 1)
// bit 6 (TWEA) is not set because we have nothing to acknowledge
// bit 5 (TWSTA) is set since we want to issue a start
// bit 4 (TWSTO) is not set because we don't want to issue a stop
// bit 3 (TWCC) is not set because there is no collision
// bit 2 (TWEN) is set because we want to keep TWI on
// bit 1 is not used
// bit 0 (TWIE) is not set because this implementation is synchronous and does not use interrupts
#define START 0b10100100
#define START_DONE 0x08
#define REPEATED_START 0x10

void i2c_init() {
//    sei(); // no need because we're not using interrupts right now
    
    // enable 2-wire on TWI1 (PE0 and PE1)
    TWCR1 |= (1 << TWEN);
    TWBR1 = 72;
    TWSR1 &= ~((1 << TWPS1) | (1 << TWPS0));
}

int i2c_send(uint8_t addr, uint8_t* data, int n, bool send_stop, bool is_repeated_start) {
    // write the data to the transmission buffer
    
    // start the two wire 
            
    // TWEN, TWSTA, TWINT must be on to start
    // note TWEN = 2
    // TWSTA = 5
    // TWINT = 7
    // so the overall bit string is 0b1x10x10x
    // noting that the 0 values help signal this is
    // a master transmitter setup
    TWCR1 |= (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
     printf("STARTING WRITE\n\r");
     printf("waiting for start sent\n\r");
    while (!(TWCR1 & (1 << TWINT))); // wait for TWINT to be set
     printf("done waiting for start sent\n\r");
    
     printf("checking status of start\n\r");
     printf("got TWSR of %d\n\r", TWSR1);
    
    uint8_t expected_status = is_repeated_start ? REPEATED_START : START_DONE;

    printf("After start\n\r");
    printf("expected status: %d (0x%x)\n\r", expected_status, expected_status);
    printf("TWSR1: %d (0x%x)\n\r", TWSR1, TWSR1);
    if ((TWSR1 & TWSR_BIT_MASK) != expected_status) {
        return -1;
    }
    
    TWDR1 = (addr << 1) | 0b0; // last bit indicates write 
    // clear the TWINT bit to start the transmission (note: clearing it means setting it to 1, which is 
    // a little counterintuitive)
    TWCR1   = (1 << TWINT) | (1 << TWEN);

    // interrupt flag is
     printf("waiting for addr sent\n\r");
    while (!(TWCR1 & (1<<TWINT)));
     printf("addr done sending\n\r");

    // Wait for an ack
     printf("waiting for ack of addr\n\r");
    if ((TWSR1 & TWSR_BIT_MASK) != MT_SLA_ACK) {
        printf("nack of addr recieved :( TWSR1 0x%x\n\r", TWSR1 & TWSR_BIT_MASK);
        return -2;
    }
     printf("ack of addr recieved\n\r");
    for (int i = 0; i < n; i++) {
        TWDR1 = data[i];
        TWCR1 = (1 << TWINT) | (1 << TWEN);
        while (!(TWCR1 & (1 << TWINT)));
        
        if ((TWSR1 & TWSR_BIT_MASK) != MT_DATA_ACK) {
            printf("nack of data[%d] received :( TWSR1 0x%x\n\r", i, TWSR1 & TWSR_BIT_MASK);
            return -3;
        }
        // printf("ack of data[%d] (value: %x) received TWSR1\n\r", i, data[i]);
    }
    
    // stop transmission
    if (send_stop) {   
        TWCR1 = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
    }
    // NOTE: don't need to check the stop condition was properly recieved
    
    return 0;
}

int i2c_recieve(uint8_t addr, uint8_t* data, int n, bool send_stop, bool is_repeated_start) {    
    TWCR1 = START;
    
    // printf("STARTING READ\n\r");
    // printf("waiting for start sent\n\r");
    while (!(TWCR1 & (1 << TWINT))); // wait for TWINT to be set
    // printf("done waiting for start sent\n\r");
    
    // printf("checking status of start\n\r");
    // // printf("got TWSR of %d\n\r", TWSR1);
    uint8_t expected_status = is_repeated_start ? REPEATED_START : START_DONE;
    if ((TWSR1 & TWSR_BIT_MASK) != expected_status) {
        return -1;
    }
    
    TWDR1 = (addr << 1) | 0b1; // last bit indicates read 
    // clear the TWINT bit
    TWCR1 = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);

    // printf("waiting for addr sent\n\r");
    while (!(TWCR1 & (1<<TWINT)));
    // printf("addr done sending\n\r");

    // Wait for an ack
    printf("waiting for ack of addr\n\r");
    if ((TWSR1 & TWSR_BIT_MASK) != MR_SLA_ACK) {
        printf("nack of addr recieved :( TWSR1 0x%x\n\r", TWSR1 & TWSR_BIT_MASK);
        return -2;
    }
    // printf("ack of addr recieved\n\r");
    
    for (int i = 0; i < n; i++) {
        uint8_t expected_status;
        if (i == n-1) {
            // send a nack to say you don't want more bytes
            TWCR1 = (1 << TWINT) | (1 << TWEN);
            expected_status = MR_DATA_NACK;
        } else {
            // send an ack to say that you do want more bytes
            TWCR1 = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
            expected_status = MR_DATA_ACK;
        }
        
        while (!(TWCR1 & (1 << TWINT)));
        
        data[i] = TWDR1;
        
        if ((TWSR1 & TWSR_BIT_MASK) != expected_status) {
            // printf("unexpected status for data[%d] received :( TWSR1 0x%x\n\r", i, TWSR1 & TWSR_BIT_MASK);
            return -3;
        }
        // printf("appropriate status for read; set data[%d] received TWSR1, data %d\n\r", i, TWDR1);
    }
    
    // stop transmission
    if (send_stop) {
        TWCR1 = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
    }
    // NOTE: don't need to check the stop condition was properly recieved
    
    return 0;
}

int i2c_write_register_8(uint8_t addr, uint8_t reg, uint8_t data) {
    uint8_t buf [2] = {reg, data};
    return i2c_send(addr, buf, 2, true, false);
}

int i2c_read_register_8(uint8_t addr, uint8_t reg, uint8_t* result) {
    // first send a byte without stop
    uint8_t buf [1] = {reg};
    int status = i2c_send(addr, buf, 1, false, false); // don't send a stop
    if (status < 0) return status;
    // then receive the result
    return i2c_recieve(addr, result, 1, true, true); // read 1 byte into result; is a repeated start
}
