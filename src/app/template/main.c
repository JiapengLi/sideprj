#include <stdint.h>
#include "hal.h"
#include "hal-uart.h"


int main(void)
{
    uint32_t ms[10];
    uint32_t flag = 1;
	uart_cfg_t uart_cfg;
    uint8_t chByte;
    
    hal_clk_init();
    
    hal_gpio_init(P0_31, GPIO_OUTPUT);
    hal_gpio_init(P0_30, GPIO_OUTPUT);
    hal_gpio_init(P0_29, GPIO_OUTPUT);
    hal_gpio_write(P0_31, 1);
    hal_gpio_write(P0_30, 1);
    hal_gpio_write(P0_29, 1);
    
    hal_gpio_init(P1_07, GPIO_OUTPUT);
    
    hal_gpio_init(P0_19, GPIO_INPUT_PU);
    
    
    uart_cfg.baudrate = 9600;
    uart_cfg.data_bits = 8;
    uart_cfg.parity = NONE;
    uart_cfg.stop_bits = 1;
    hal_uart_init(UART_0, P0_16, P0_15, &uart_cfg);
    
    while(!hal_uart_tx(UART_0, 'J'));
    while(!hal_uart_tx(UART_0, 'i'));
    while(!hal_uart_tx(UART_0, 'a'));
    while(!hal_uart_tx(UART_0, 'p'));
    while(!hal_uart_tx(UART_0, 'e'));
    while(!hal_uart_tx(UART_0, 'n'));
    while(!hal_uart_tx(UART_0, 'g'));
    while(!hal_uart_tx(UART_0, 'L'));
    while(!hal_uart_tx(UART_0, 'i'));
    while(!hal_uart_tx(UART_0, '\r'));
    while(!hal_uart_tx(UART_0, '\n'));
    
    while (1) {
        /* M.2 Dock LED blinking */
        if ((millis() - ms[0]) > 500) {
            ms[0] = millis();

            hal_gpio_write(P1_07, flag % 2);
            
            flag++;
            
            //hal_uart_tx(UART_0, 'C');
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
        
        if (hal_uart_rx(UART_0, &chByte)) {
            hal_uart_tx(UART_0, chByte);
        }

        hal_systick_emu_evt();
    }
    
    //test(str);
}
