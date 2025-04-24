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

#define LSM6DSO_FUNC_CFG_ACCESS      0x01
#define LSM6DSO_PIN_CTRL             0x02
// Reserved addresses 0x03-0x06
#define LSM6DSO_FIFO_CTRL1           0x07
#define LSM6DSO_FIFO_CTRL2           0x08
#define LSM6DSO_FIFO_CTRL3           0x09
#define LSM6DSO_FIFO_CTRL4           0x0A
#define LSM6DSO_COUNTER_BDR_REG1     0x0B
#define LSM6DSO_COUNTER_BDR_REG2     0x0C
#define LSM6DSO_INT1_CTRL            0x0D
#define LSM6DSO_INT2_CTRL            0x0E
#define LSM6DSO_WHO_AM_I             0x0F
#define LSM6DSO_CTRL1_XL             0x10
#define LSM6DSO_CTRL2_G              0x11
#define LSM6DSO_CTRL3_C              0x12
#define LSM6DSO_CTRL4_C              0x13
#define LSM6DSO_CTRL5_C              0x14
#define LSM6DSO_CTRL6_C              0x15
#define LSM6DSO_CTRL7_G              0x16
#define LSM6DSO_CTRL8_XL             0x17
#define LSM6DSO_CTRL9_XL             0x18
#define LSM6DSO_CTRL10_C             0x19
#define LSM6DSO_ALL_INT_SRC          0x1A
#define LSM6DSO_WAKE_UP_SRC          0x1B
#define LSM6DSO_TAP_SRC              0x1C
#define LSM6DSO_D6D_SRC              0x1D
#define LSM6DSO_STATUS_REG           0x1E
// RESERVED address 0x1F
#define LSM6DSO_OUT_TEMP_L           0x20
#define LSM6DSO_OUT_TEMP_H           0x21
#define LSM6DSO_OUTX_L_G             0x22
#define LSM6DSO_OUTX_H_G             0x23
#define LSM6DSO_OUTY_L_G             0x24
#define LSM6DSO_OUTY_H_G             0x25
#define LSM6DSO_OUTZ_L_G             0x26
#define LSM6DSO_OUTZ_H_G             0x27
#define LSM6DSO_OUTX_L_A             0x28
#define LSM6DSO_OUTX_H_A             0x29
#define LSM6DSO_OUTY_L_A             0x2A
#define LSM6DSO_OUTY_H_A             0x2B
#define LSM6DSO_OUTZ_L_A             0x2C
#define LSM6DSO_OUTZ_H_A             0x2D
// RESERVED addresses 0x2E-0x34
#define LSM6DSO_EMB_FUNC_STATUS_MAINPAGE   0x35
#define LSM6DSO_FSM_STATUS_A_MAINPAGE      0x36
#define LSM6DSO_FSM_STATUS_B_MAINPAGE      0x37
// RESERVED address 0x38
#define LSM6DSO_STATUS_MASTER_MAINPAGE     0x39
#define LSM6DSO_FIFO_STATUS1               0x3A
#define LSM6DSO_FIFO_STATUS2               0x3B
// RESERVED addresses 0x3C-0x3F
#define LSM6DSO_TIMESTAMP0                 0x40
#define LSM6DSO_TIMESTAMP1                 0x41
#define LSM6DSO_TIMESTAMP2                 0x42
#define LSM6DSO_TIMESTAMP3                 0x43
// RESERVED addresses 0x44-0x55
#define LSM6DSO_TAP_CFG0            0x56
#define LSM6DSO_TAP_CFG1            0x57
#define LSM6DSO_TAP_CFG2            0x58
#define LSM6DSO_TAP_THS_6D          0x59
#define LSM6DSO_INT_DUR2            0x5A
#define LSM6DSO_WAKE_UP_THS         0x5B
#define LSM6DSO_WAKE_UP_DUR         0x5C
#define LSM6DSO_FREE_FALL           0x5D
#define LSM6DSO_MD1_CFG             0x5E
#define LSM6DSO_MD2_CFG             0x5F
// RESERVED addresses 0x60-0x61
#define LSM6DSO_I3C_BUS_AVB         0x62
#define LSM6DSO_INTERNAL_FREQ_FINE  0x63
// RESERVED addresses 0x64-0x6E
#define LSM6DSO_INT_OIS             0x6F
#define LSM6DSO_CTRL1_OIS           0x70
#define LSM6DSO_CTRL2_OIS           0x71
#define LSM6DSO_CTRL3_OIS           0x72
#define LSM6DSO_X_OFS_USR           0x73

#ifndef LSM6DS0_I2C_ADDR
    #warning "IMU_I2C_ADDR not defined. Defaulting to 0b1101011 (IMU_I2C_ADDR_1)"
    #define LSM6DS0_I2C_ADDR LSM6DS0_I2C_ADDR_1
#endif


#define LSM6DS0_WHO_AM_I 0x0F


int lsm6ds0_write_register_8(uint8_t reg, uint8_t value);

int lsm6ds0_read_register_8(uint8_t reg, uint8_t* result);

int lsm6ds0_init(void);

#endif	/* LSM6DS0_H */

