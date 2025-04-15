/* 
 * File:   lsm6ds0.h
 * Author: aagam
 *
 * Created on April 15, 2025, 5:32 AM
 */

#ifndef LSM6DS0_H
#define	LSM6DS0_H

// the last bit 0
#define LSM6DS0_I2C_ADDR_0 0b1101010
#define LSM6DS0_I2C_ADDR_1 0b1101011

#ifndef LSM6DS0_I2C_ADDR
    #warning "IMU_I2C_ADDR not defined. Defaulting to 0b1101010 (IMU_I2C_ADDR_0)"
    #define LSM6DS0_I2C_ADDR LSM6DS0_I2C_ADDR_0
#endif


#define LSM6DS0_WHO_AM_I 0x0F


int lsm6ds0_write_register_8(uint8_t reg, uint8_t value);

int lsm6ds0_read_register_8(uint8_t reg, uint8_t* result);

int lsm6ds0_init(void);

#endif	/* LSM6DS0_H */

