#ifndef __HAL_SYSTICK_EMU_H
#define __HAL_SYSTICK_EMU_H

#include <stdint.h>

extern void hal_systick_emu_evt(void);
extern uint32_t hal_systick_emu_millis(void);

#endif
