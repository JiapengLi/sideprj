#include "nrf.h"

#include <stdint.h>
#include "hal-gpio.h"

void systick_evt(void);
uint32_t millis(void);

#define SYSTICK_TIME_PER_TICK               (500)           // ns
#define SYSTICK_1MS                         (1000000)       // ns

static volatile uint32_t systick_cnt = 0;
static volatile uint32_t systick_cnt_ms = 0;

void systick_evt(void)
{
    systick_cnt += SYSTICK_TIME_PER_TICK;
    while (systick_cnt >= SYSTICK_1MS) {
        systick_cnt -= SYSTICK_1MS;
        systick_cnt_ms++;
    }
}

uint32_t millis(void)
{
    return systick_cnt_ms;
}

int main(void)
{
    uint32_t ms[10];
    uint32_t flag = 1;
	
    /* enable 64MHz clock sourced by external 32MHz crystal */
    NRF_CLOCK->TASKS_HFCLKSTART = 0x1;
    while ((NRF_CLOCK->HFCLKSTAT & 0x1) != 0x1);

    hal_gpio_init(P0_31, GPIO_OUTPUT);
    hal_gpio_init(P0_30, GPIO_OUTPUT);
    hal_gpio_init(P0_29, GPIO_OUTPUT);
    hal_gpio_write(P0_31, 1);
    hal_gpio_write(P0_30, 1);
    hal_gpio_write(P0_29, 1);
    
    hal_gpio_init(P1_07, GPIO_OUTPUT);
    
    hal_gpio_init(P0_19, GPIO_INPUT_PU);
    
    while (1) {
        /* M.2 Dock LED blinking */
        if ((millis() - ms[0]) > 500) {
            ms[0] = millis();

            hal_gpio_write(P1_07, flag % 2);
            
            flag++;
        }
        
        /* KEY & LED */
        if ((millis() - ms[1]) > 5) {
            ms[1] = millis();
            if (hal_gpio_read(P0_19)) {
                hal_gpio_write(P0_29, 1);
            } else {
                hal_gpio_write(P0_29, 0);
            }
        }
        
        systick_evt();
    }
}
