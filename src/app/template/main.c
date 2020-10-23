#include <stdint.h>
#include "hal.h"

int main(void)
{
    uint32_t ms[10];
    uint32_t flag = 1;
	
    hal_gpio_init(P0_31, GPIO_OUTPUT);
    hal_gpio_init(P0_30, GPIO_OUTPUT);
    hal_gpio_init(P0_29, GPIO_OUTPUT);
    hal_gpio_write(P0_31, 1);
    hal_gpio_write(P0_30, 1);
    hal_gpio_write(P0_29, 1);
    
    hal_gpio_init(P1_07, GPIO_OUTPUT);
    
    hal_gpio_init(P0_19, GPIO_INPUT_PU);
    
    while (1) {
        /* M.2 Dock LED blinking */
        if ((millis() - ms[0]) > 500) {
            ms[0] = millis();

            hal_gpio_write(P1_07, flag % 2);
            
            flag++;
        }
        
        /* KEY & LED */
        if ((millis() - ms[1]) > 5) {
            ms[1] = millis();
            if (hal_gpio_read(P0_19)) {
                hal_gpio_write(P0_29, 1);
            } else {
                hal_gpio_write(P0_29, 0);
            }
        }
        
        hal_systick_emu_evt();
    }
}
