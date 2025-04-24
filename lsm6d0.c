#include "i2c.h"
#include "lsm6ds0.h"

int lsm6ds0_write_register_8(uint8_t reg, uint8_t value) {
    return i2c_write_register_8(LSM6DS0_I2C_ADDR, reg, value);
}

int lsm6ds0_read_register_8(uint8_t reg, uint8_t* result) {
    return i2c_read_register_8(LSM6DS0_I2C_ADDR, reg, result);
}

int lsm6ds0_init(void) {
}