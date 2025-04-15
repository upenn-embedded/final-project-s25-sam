#include "drv2605.h"
#include "i2c.h"
#include <stdio.h>

int drv2605_write_register_8(uint8_t reg, uint8_t value) {
    uint8_t buf [2] = {reg, value};
    return i2c_send(DRV2605_I2C_ADDR, buf, 2, true, false);
}

int drv2605_read_register_8(uint8_t reg, uint8_t* result) {
    // first send a byte without stop
    uint8_t buf [1] = {reg};
    int status = i2c_send(DRV2605_I2C_ADDR, buf, 1, false, false); // don't send a stop
    if (status < 0) return status;
    return i2c_recieve(DRV2605_I2C_ADDR, result, 1, true, true); // read 1 byte into result; is a repeated start
}

// Initialize DRV2605
int drv2605_init(void) {
    int status;
    
    // reset the device
    status = drv2605_write_register_8(DRV2605_REG_MODE, 0x80);  // Set reset bit
    if (status != 0) return status;
    _delay_ms(10);  // Wait for reset to complete
        
    // set the device to standby mode first
    status = drv2605_write_register_8(DRV2605_REG_MODE, 0x40);  // Standby
    if (status != 0) return status;
    
    // voltage - our pancake motor has a voltage rating of 2.5-3.8V
    status = drv2605_write_register_8(DRV2605_REG_RATED_VOLTAGE, 143);  // ~3V (see 7.5.2 of https://cdn-shop.adafruit.com/datasheets/DRV2605.pdf#page=20&zoom=100,0,509)
    if (status != 0) return status;
    
    // Configure the overdrive voltage
    status = drv2605_write_register_8(DRV2605_REG_OVERDRIVE_CLAMP, 167); // ~3.5V
    if (status != 0) return status;
    
    // Configure the feedback control register for ERM motors
    // Bit 7 = ERM or LRA mode (set to 0 for ERM)
    // Bit 6-4 = FB_BRAKE_FACTOR - use default value of 3
    // BIT 3-2 = LOOP_GAIN - use default value of 1
    // BIT 1-0 = BEMF_GAIN - use default value of 2 (this will also be set by auto calibration)
    // From 7.6.20 https://cdn-shop.adafruit.com/datasheets/DRV2605.pdf#page=20&zoom=100,0,509    
    status = drv2605_write_register_8(DRV2605_REG_FEEDBACK_CONTROL, 0b00110110);
    if (status != 0) return status;
    
    drv2605_write_register_8(DRV2605_REG_MODE, 0x07);  // Auto-calibration mode
    drv2605_write_register_8(DRV2605_REG_GO, 0x01);
    
    // wait for calibration to complete
    while (1) {
        uint8_t go_bit;
        status = drv2605_read_register_8(DRV2605_REG_GO, &go_bit) & 0x01;
        if (status != 0) return status;
        if (go_bit == 0) break;
        _delay_ms(10);
    }
    
    uint8_t status_reg_val;
    status = drv2605_read_register_8(DRV2605_REG_STATUS, &status_reg_val);
    if (status != 0) return status;
    if (status_reg_val & 0x08) {
        printf("Calibration error detected\n\r");
        return -999;
    }
    
    // Set the library to A
    status = drv2605_write_register_8(DRV2605_REG_LIBRARY, LIB_ERM_A);  // ERM Library A
    if (status != 0) return status;
    
    // Set mode to internal trigger (ready to accept GO commands)
    status = drv2605_write_register_8(DRV2605_REG_MODE, MODE_INTERNAL_TRIGGER);
    if (status != 0) return status;
    
    return 0;
}
