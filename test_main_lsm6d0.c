#include "i2c.h"
#include "uart.h"
#include "lsm6ds0.h"
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 16_000_000

// by default, the address is LSM6DS0_I2C_ADDR_1
#define LSM6DS0_I2C_ADDR LSM6DS0_I2C_ADDR_1

int main(int argc, char** argv) {
    // transmit to this peripheral
    i2c_init();
    uart_init();
    char* data = "hello world!";
    
    int status;    
    lsm6ds0_init();
    
    for (int i = 0; 1   ; i++) {
//        printf("%s", data);
//        uint8_t request[1] = {LSM6DS0_WHO_AM_I_REG};
        uint8_t response[1] = {0};
//        i2c_send(LSM6DS0_I2C_ADDR_1, request, 1, false, false);
//        i2c_recieve(LSM6DS0_I2C_ADDR_1, response, 1, true, true);
        
        _delay_ms(100);
        status = lsm6ds0_read_register_8(LSM6DS0_WHO_AM_I_REG, response);
//        printf("READING WHO AM I; got status %d; got result %d; expected %d\n\r", status, response[0], 0x6C);
    }
    
    // status = drv2605_read_register_8(DRV2605_REG_LIBRARY, &res);
    // printf("READING MODE; got status %d; got result %d; expected %d\n\r", status, res, LIB_ERM_A);
    
    // status = drv2605_write_register_8(DRV2605_REG_WAVESEQ1, 0x01);
    // printf("WRITING WAVESQ1; got status %d\n\r", status);
    // status = drv2605_write_register_8(DRV2605_REG_GO, 0x01);
    // printf("WRITING GO; got status %d\n\r", status);

    //i2c_send(DRV2605_I2C_ADDR, data, 13); // also write the null terminator just for fun

//        i2c_recieve(IMU_I2C_ADDR_0, data, 13); // expect to read things back
//    _delay_ms(50);

    while (1);
    return 0;
}

