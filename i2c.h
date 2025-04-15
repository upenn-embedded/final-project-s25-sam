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
 * @param addr
 * @param data
 * @param n
 */
int i2c_recieve(uint8_t addr, uint8_t* data, int n, bool send_stop, bool is_repeated_start);

/**
 * Send in master transmitter mode
 * @param addr
 * @param data
 * @param n
 * @return 
 */
int i2c_send(uint8_t addr, uint8_t* data, int n, bool send_stop, bool is_repeated_start);

void i2c_init();

#endif	/* I2C_H */

