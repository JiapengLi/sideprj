#include "hal.h"

uint32_t millis(void)
{
    return hal_systick_emu_millis();
}
