#include "nrf.h"
#include "hal-gpio.h"

void hal_gpio_init(gpio_t gpio, gpio_cfg_t cfg)
{
    NRF_GPIO_Type *port = (NRF_GPIO_Type *)(NRF_P0_BASE + (gpio / 32) * 0x300);
    
    port->PIN_CNF[gpio % 32] = ((uint32_t)((cfg >> 0) & 0xF) << GPIO_PIN_CNF_DIR_Pos)
                             | ((uint32_t)((cfg >> 4) & 0xF) << GPIO_PIN_CNF_INPUT_Pos)
                             | ((uint32_t)((cfg >> 8) & 0xF) << GPIO_PIN_CNF_PULL_Pos)
                             | ((uint32_t)((cfg >> 12) & 0xF) << GPIO_PIN_CNF_DRIVE_Pos)
                             | ((uint32_t)((cfg >> 16) & 0xF) << GPIO_PIN_CNF_SENSE_Pos);
}

void hal_gpio_write(gpio_t gpio, uint32_t val)
{
    NRF_GPIO_Type *port = (NRF_GPIO_Type *)(NRF_P0_BASE + (gpio / 32) * 0x300);

    
    if (val) {
        port->OUTSET = 1UL << (gpio % 32);
    } else {
        port->OUTCLR = 1UL << (gpio % 32);
    }
}

uint32_t hal_gpio_read(gpio_t gpio)
{
    NRF_GPIO_Type *port = (NRF_GPIO_Type *)(NRF_P0_BASE + (gpio / 32) * 0x300);
    
    if (port->IN & (1UL << (gpio % 32))) {
        return 1;
    } else {
        return 0;
    }
}





