#include <stdint.h>
#include "hal.h"
#include "hal-uart.h"


int main(void)
{
    uint32_t ms;
    uint32_t ledsta = 0;
    
    system_init();
    
    while(!serial_out('J'));
    while(!serial_out('i'));
    while(!serial_out('a'));
    while(!serial_out('p'));
    while(!serial_out('e'));
    while(!serial_out('n'));
    while(!serial_out('g'));
    while(!serial_out('L'));
    while(!serial_out('i'));
    while(!serial_out('\r'));
    while(!serial_out('\n'));
    
    while (1) {
        uint8_t chByte;
        
        if (IS_KEY1_DOWN()) {
            LED1_ON();
        }  else  {
            LED1_OFF();
        }		
       
        if (serial_in(&chByte)) {
            serial_out(chByte);
        }
        
        breathled();
        
        if ((millis() - ms) >= 1000) {
            ms = millis();
            
            hal_gpio_write(LED3_PIN, ledsta % 2);
            ledsta++;
        }
        
        hal_systick_emu_evt();
    }
}
