/* 
 * File:   i2c.h
 * Author: aagam
 *
 * Created on April 15, 2025, 12:39 AM
 */

#ifndef I2C_H
#define	I2C_H

#include <stdint.h>
#include <stdbool.h>


/**
 * Recieve data in master reciever mode
 */
int i2c_recieve(uint8_t addr, uint8_t* data, int n, bool send_stop, bool is_repeated_start);

/**
 * Send in master transmitter mode
 */
int i2c_send(uint8_t addr, uint8_t* data, int n, bool send_stop, bool is_repeated_start);

void i2c_init();

int i2c_write_register_8(uint8_t addr, uint8_t reg, uint8_t data);

int i2c_read_register_8(uint8_t addr, uint8_t reg, uint8_t* result);

#endif	/* I2C_H */

