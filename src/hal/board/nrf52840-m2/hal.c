#include "hal.h"
#include "hal-uart.h"

void system_init(void)
{
    uart_cfg_t uart_cfg;
    
    hal_clk_init();
    
    hal_gpio_init(LED1_PIN, GPIO_OUTPUT);
    hal_gpio_init(LED2_PIN, GPIO_OUTPUT);
    hal_gpio_write(LED1_PIN, LED_OFF);
    hal_gpio_write(LED2_PIN, LED_OFF);

    hal_gpio_init(KEY1_PIN, GPIO_INPUT_PU);
    hal_gpio_init(KEY2_PIN, GPIO_INPUT_PU);
    
    uart_cfg.baudrate = 9600;
    uart_cfg.data_bits = 8;
    uart_cfg.parity = NONE;
    uart_cfg.stop_bits = 1;
    hal_uart_init(UART_0, P0_16, P0_15, &uart_cfg);

}

bool serial_in(uint8_t *dt)
{
    return hal_uart_rx(UART_0, dt);
}

bool serial_out(uint8_t dt)
{
    return hal_uart_tx(UART_0, dt);
}

uint32_t millis(void)
{
    return hal_systick_emu_millis();
}
