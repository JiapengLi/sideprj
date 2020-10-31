#include "nrf.h"
#include "hal-gpio.h"

/*
NOTE:
    - `gpio >> 5` is equal to `gpio / 32`
    - `gpio & 0x1F` is equal to `gpio % 32`
    - the purpose of these is to save MCU compute time (a downside is make it difficult to read code for ordinary programer)
*/

void hal_gpio_init(gpio_t tGpio, gpio_cfg_t tCfg)
{
    NRF_GPIO_Type *ptPort = (NRF_GPIO_Type *)(NRF_P0_BASE + (tGpio >> 5) * 0x300);

    ptPort->PIN_CNF[tGpio & 0x1F] = ((uint32_t)((tCfg >> 0) & 0xF) << GPIO_PIN_CNF_DIR_Pos)
                                   | ((uint32_t)((tCfg >> 4) & 0xF) << GPIO_PIN_CNF_INPUT_Pos)
                                   | ((uint32_t)((tCfg >> 8) & 0xF) << GPIO_PIN_CNF_PULL_Pos)
                                   | ((uint32_t)((tCfg >> 12) & 0xF) << GPIO_PIN_CNF_DRIVE_Pos)
                                   | ((uint32_t)((tCfg >> 16) & 0xF) << GPIO_PIN_CNF_SENSE_Pos);
}

void hal_gpio_write(gpio_t tGpio, uint32_t wVal)
{
    NRF_GPIO_Type *ptPort = (NRF_GPIO_Type *)(NRF_P0_BASE + (tGpio >> 5) * 0x300);

    if (wVal) {
        ptPort->OUTSET = 1UL << (tGpio & 0x1F);
    } else {
        ptPort->OUTCLR = 1UL << (tGpio & 0x1F);
    }
}

uint32_t hal_gpio_read(gpio_t tGpio)
{
    NRF_GPIO_Type *ptPort = (NRF_GPIO_Type *)(NRF_P0_BASE + (tGpio >> 5) * 0x300);

    if (ptPort->IN & (1UL << (tGpio & 0x1F))) {
        return 1;
    } else {
        return 0;
    }
}





