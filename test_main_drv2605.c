// A main to test communicating with the drv2605
// It makes it buzz!

#include "i2c.h"
#include "uart.h"
#include "drv2605.h"
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 16_000_000

// the last bit 0
#define IMU_I2C_ADDR_0 0b1101010
#define IMU_I2C_ADDR_1 0b1101011

/*
 * 
 */
int main(int argc, char** argv) {
    // transmit to this peripheral
    i2c_init();
    uart_init();
    char* data = "hello world!";
    printf("%s", data);
    
    int status;
    uint8_t res;
    
    drv2605_init();
    
    status = drv2605_read_register_8(DRV2605_REG_GO, &res);
    printf("READING GO; got status %d; got result %d; expected %d\n\r", status, res, 0);
    
    status = drv2605_read_register_8(DRV2605_REG_LIBRARY, &res);
    printf("READING MODE; got status %d; got result %d; expected %d\n\r", status, res, LIB_ERM_A);
    
    status = drv2605_write_register_8(DRV2605_REG_WAVESEQ1, 0x01);
    printf("WRITING WAVESQ1; got status %d\n\r", status);
    status = drv2605_write_register_8(DRV2605_REG_GO, 0x01);
    printf("WRITING GO; got status %d\n\r", status);

    //i2c_send(DRV2605_I2C_ADDR, data, 13); // also write the null terminator just for fun

//        i2c_recieve(IMU_I2C_ADDR_0, data, 13); // expect to read things back
//    _delay_ms(50);

    while (1);
    return 0;
}

