#include "hal.h"

static volatile uint32_t systick_cnt = 0;
static volatile uint32_t systick_cnt_ms = 0;

void hal_systick_emu_evt(void)
{
    systick_cnt += SYSTICK_TIME_PER_TICK;
    while (systick_cnt >= SYSTICK_1MS) {
        systick_cnt -= SYSTICK_1MS;
        systick_cnt_ms++;
    }
}

uint32_t hal_systick_emu_millis(void)
{
    return systick_cnt_ms;
}


