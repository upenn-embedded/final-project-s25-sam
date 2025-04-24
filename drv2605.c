#include "drv2605.h"
#include "i2c.h"
#include <stdio.h>

int
drv2605_write_register_8(uint8_t reg, uint8_t value) {
    return i2c_write_register_8(DRV2605_I2C_ADDR, reg, value);
}

int
drv2605_read_register_8(uint8_t reg, uint8_t *result) {
    return i2c_read_register_8(DRV2605_I2C_ADDR, reg, result);
}

// Initialize DRV2605
int
drv2605_init(void) {
    int status;

    // reset the device
    status = drv2605_write_register_8(DRV2605_REG_MODE, 0x80);   // Set reset bit
    if (status != 0)
        return status;

    // set the device to standby mode first
    status = drv2605_write_register_8(DRV2605_REG_MODE, 0x40);   // Standby
    if (status != 0)
        return status;

    // voltage - our pancake motor has a voltage rating of 2.5-3.8V
    status = drv2605_write_register_8(DRV2605_REG_RATED_VOLTAGE, 143);   // ~3V (see 7.5.2 of https://cdn-shop.adafruit.com/datasheets/DRV2605.pdf#page=20&zoom=100,0,509)
    if (status != 0)
        return status;

    // Configure the overdrive voltage
    status = drv2605_write_register_8(DRV2605_REG_OVERDRIVE_CLAMP, 167);   // ~3.5V
    if (status != 0)
        return status;

    // Configure the feedback control register for ERM motors
    // Bit 7 = ERM or LRA mode (set to 0 for ERM)
    // Bit 6-4 = FB_BRAKE_FACTOR - use default value of 3
    // BIT 3-2 = LOOP_GAIN - use default value of 1
    // BIT 1-0 = BEMF_GAIN - use default value of 2 (this will also be set by auto calibration)
    // From 7.6.20 https://cdn-shop.adafruit.com/datasheets/DRV2605.pdf#page=20&zoom=100,0,509
    status = drv2605_write_register_8(DRV2605_REG_FEEDBACK_CONTROL, 0b00110110);
    if (status != 0)
        return status;

    drv2605_write_register_8(DRV2605_REG_MODE, 0x07);   // Auto-calibration mode
    drv2605_write_register_8(DRV2605_REG_GO, 0x01);

    // wait for calibration to complete
    _delay_ms(3000);

    uint8_t status_reg_val;
    status = drv2605_read_register_8(DRV2605_REG_STATUS, &status_reg_val);
    if (status != 0)
        return status;
    if (status_reg_val & 0x08) {
        printf("Calibration error detected\n\r");
        return -999;
    }

    // Set the library to A
    status = drv2605_write_register_8(DRV2605_REG_LIBRARY, LIB_ERM_A);   // ERM Library A
    if (status != 0)
        return status;

    // Set mode to internal trigger (ready to accept GO commands)
    status = drv2605_write_register_8(DRV2605_REG_MODE, MODE_INTERNAL_TRIGGER);
    if (status != 0)
        return status;

    return 0;
}
