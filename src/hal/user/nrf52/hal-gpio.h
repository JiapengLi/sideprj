#ifndef __HAL_GPIO_H
#define __HAL_GPIO_H

#include <stdint.h>

typedef enum {
    P0_00 = 0, P0_01, P0_02, P0_03, P0_04, P0_05, P0_06, P0_07,
    P0_08, P0_09, P0_10, P0_11, P0_12, P0_13, P0_14, P0_15,
    P0_16, P0_17, P0_18, P0_19, P0_20, P0_21, P0_22, P0_23, 
    P0_24, P0_25, P0_26, P0_27, P0_28, P0_29, P0_30, P0_31, 
    P1_00, P1_01, P1_02, P1_03, P1_04, P1_05, P1_06, P1_07, 
    P1_08, P1_09, P1_10, P1_11, P1_12, P1_13, P1_14, P1_15, 
    P1_16, P1_17, P1_18, P1_19, P1_20, P1_21, P1_22, P1_23, 
    P1_24, P1_25, P1_26, P1_27, P1_28, P1_29, P1_30, P1_31,
} gpio_t;


/* SENSE / DRV / PULL / INPUT_EN / DIR */
typedef enum {
    GPIO_INPUT          = 0x00000,
    GPIO_OUTPUT         = 0x03011,
    GPIO_OUTPUT_PP      = GPIO_OUTPUT,
    GPIO_OUTPUT_OD      = 0x07001,
    GPIO_ALT            = 0x00000,
    GPIO_ANALOG         = 0x00000,

    GPIO_INPUT_PU       = 0x00300,
    GPIO_OUTPUT_PP_PU   = 0x03311,
    GPIO_OUTPUT_OD_PU   = 0x07301,
    GPIO_ALT_PP_PU      = 0x00000,
    GPIO_ALT_OD_PU      = 0x00000,

    GPIO_INPUT_PD       = 0x00100,
    GPIO_OUTPUT_PP_PD   = 0x03111,
    GPIO_OUTPUT_OD_PD   = 0x07101,
    GPIO_ALT_PD         = 0x00000,
    GPIO_ALT_PP_PD      = 0x00000,
    GPIO_ALT_OD_PD      = 0x00000,
} gpio_cfg_t;

extern void hal_gpio_init(gpio_t tGpio, gpio_cfg_t tCfg);
extern void hal_gpio_write(gpio_t tPin, uint32_t wVal);
extern uint32_t hal_gpio_read(gpio_t tPin);

#endif
