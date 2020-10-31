#include "hal.h"

static volatile uint32_t s_wSysTickCnt = 0;
static volatile uint32_t s_wSysTickCntMs = 0;

void hal_systick_emu_evt(void)
{
    s_wSysTickCnt += SYSTICK_TIME_PER_TICK;
    while (s_wSysTickCnt >= SYSTICK_1MS) {
        s_wSysTickCnt -= SYSTICK_1MS;
        s_wSysTickCntMs++;
    }
}

uint32_t hal_systick_emu_millis(void)
{
    return s_wSysTickCntMs;
}
