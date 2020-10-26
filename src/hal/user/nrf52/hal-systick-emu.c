#include "hal.h"

static volatile uint32_t g_wSysTickCnt = 0;
static volatile uint32_t g_wSysTickCntMs = 0;

void hal_systick_emu_evt(void)
{
    g_wSysTickCnt += SYSTICK_TIME_PER_TICK;
    while (g_wSysTickCnt >= SYSTICK_1MS) {
        g_wSysTickCnt -= SYSTICK_1MS;
        g_wSysTickCntMs++;
    }
}

uint32_t hal_systick_emu_millis(void)
{
    return g_wSysTickCntMs;
}
