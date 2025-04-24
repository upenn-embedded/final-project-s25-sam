// A main to test communicating with the drv2605
// It makes it buzz!

#include "i2c.h"
#include "uart.h"
#include "drv2605.h"
#include "lsm6ds0.h"
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 16_000_000

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
    
    drv2605_init();
    lsm6ds0_init();
    
    while (1) {
        uint8_t lsm6ds0_whoami;
        status = lsm6ds0_read_register_8(LSM6DSO_WHO_AM_I, &lsm6ds0_whoami);
        printf("READING LSM6DSO_WHO_AM_I %d (0x%x)\n\r", lsm6ds0_whoami);
        
        status = drv2605_write_register_8(DRV2605_REG_WAVESEQ1, 0x01);
        printf("WRITING WAVESQ1; got status %d\n\r", status);
        status = drv2605_write_register_8(DRV2605_REG_GO, 0x01);
        printf("WRITING GO; got status %d\n\r", status);
        
        _delay_ms(50);
        
        
    }
    return 0;
}
