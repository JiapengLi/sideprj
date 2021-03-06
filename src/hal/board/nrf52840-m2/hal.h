#ifndef __HAL__
#define __HAL__

#include <stdbool.h>
#include <stdio.h>

#include "nrf.h"
#include "nrf52840-m2-pins.h"

#include "hal-clk.h"
#include "hal-gpio.h"
#include "hal-systick-emu.h"

#define SYSTICK_TIME_PER_TICK               (3000)              // ns
#define SYSTICK_1MS                         (1000000)           // ns

#define KEY1_PIN                            (P0_19)
#define KEY2_PIN                            (P0_20)

#define LED1_PIN                            (P0_29)
#define LED2_PIN                            (P1_07)
#define LED3_PIN                            (P0_31)

#define LED_ON                              (0)
#define LED_OFF                             (1)

#define LED1_ON()                           do{ hal_gpio_write(LED1_PIN, LED_ON); } while(0)
#define LED1_OFF()                          do{ hal_gpio_write(LED1_PIN, LED_OFF); } while(0)

#define LED2_ON()                           do{ hal_gpio_write(LED2_PIN, LED_ON); } while(0)
#define LED2_OFF()                          do{ hal_gpio_write(LED2_PIN, LED_OFF); } while(0)

#define IS_KEY1_DOWN()                      (hal_gpio_read(KEY1_PIN) == 0)
#define IS_KEY1_UP()                        (hal_gpio_read(KEY1_PIN) != 0)

#define IS_KEY2_DOWN()                      (hal_gpio_read(KEY2_PIN) == 0)
#define IS_KEY2_UP()                        (hal_gpio_read(KEY2_PIN) != 0)

extern void system_init(void);

extern bool serial_in(uint8_t *pchData);
extern bool serial_out(uint8_t chData);

extern uint32_t millis(void);

extern void breathled_init(void);
extern void breathled(void);

#endif
