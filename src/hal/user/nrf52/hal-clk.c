#include "hal.h"

void hal_clk_init(void)
{
    /* enable 64MHz clock sourced by external 32MHz crystal */
    NRF_CLOCK->TASKS_HFCLKSTART = 0x1;
    while ((NRF_CLOCK->HFCLKSTAT & 0x1) != 0x1);
}
