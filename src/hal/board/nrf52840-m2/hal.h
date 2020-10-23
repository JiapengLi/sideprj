#ifndef __HAL__
#define __HAL__

#include "nrf.h"
#include "nrf52840-m2-pins.h"

#include "hal-gpio.h"
#include "hal-systick-emu.h"

#define SYSTICK_TIME_PER_TICK               (500)           // ns
#define SYSTICK_1MS                         (1000000)       // ns

uint32_t millis(void);

#endif
