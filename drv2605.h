/* 
 * File:   drv2605.h
 * Author: aagam
 *
 * Created on April 15, 2025, 12:41 AM
 */

#ifndef DRV2605_H
#define	DRV2605_H

#include <stdint.h>
#include <util/delay.h>

// See also: https://github.com/adafruit/Adafruit_DRV2605_Library/blob/master/Adafruit_DRV2605.cpp#L198
// Which presents an interface which we mimic here

// Libraries you can choose from (0 is no library)
// Since we're using an ERM motor, we want to pick from ERM
// A-E
#define LIB_EMPTY 0
#define LIB_ERM_A 1
#define LIB_ERM_B 2
#define LIB_ERM_C 3
#define LIB_ERM_D 4
#define LIB_ERM_E 5
#define LIB_LRA 6
#define MODE_INTERNAL_TRIGGER 0x00

#define DRV2605_I2C_ADDR 0b1011010

#define DRV2605_REG_MODE         0x01
#define DRV2605_REG_LIBRARY      0x03
#define DRV2605_REG_WAVESEQ1     0x04
#define DRV2605_REG_GO           0x0C
#define DRV2605_REG_RATED_VOLTAGE    0x16
#define DRV2605_REG_OVERDRIVE_CLAMP  0x17
#define DRV2605_REG_FEEDBACK_CONTROL 0x1A
#define DRV2605_REG_CONTROL1         0x1B
#define DRV2605_REG_CONTROL2         0x1C
#define DRV2605_REG_STATUS           0x00

//void drv2605_select_library(uint8_t lib);
//
//void drv2605_go();
//
//void drv2605_stop();
//
//void drv2605_select_mode(uint8_t mode);

int drv2605_write_register_8(uint8_t reg, uint8_t value);

int drv2605_read_register_8(uint8_t reg, uint8_t* result);

int drv2605_init(void);

//void drv2605_set_waveform(uint8_t slot, uint8_t waveform);

#endif	/* DRV2605_H */

