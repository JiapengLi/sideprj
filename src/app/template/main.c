#include "nrf.h"

#include <stdint.h>

void systick_evt(void);
uint32_t millis(void);

#define SYSTICK_1MS                         (1000000)
#define SYSTICK_TIME_PER_TICK               (500)    // ns

static volatile uint32_t systick_cnt = 0;
static volatile uint32_t systick_cnt_us = 0;
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

uint32_t micros(void)
{
    return systick_cnt;
}

//P1.07

#define PIN         7

int main(void)
{
    uint32_t ms = millis();
    uint32_t us = micros();
    uint32_t pins_state;
	
    /* enable 64MHz clock sourced by external 32MHz crystal */
    NRF_CLOCK->TASKS_HFCLKSTART = 0x1;
    while ((NRF_CLOCK->HFCLKSTAT & 0x1) != 0x1);
    
    NRF_P1->PIN_CNF[PIN] = ((uint32_t)GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos)
                       | ((uint32_t)GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos)
                       | ((uint32_t)GPIO_PIN_CNF_PULL_Disabled << GPIO_PIN_CNF_PULL_Pos)
                       | ((uint32_t)GPIO_PIN_CNF_DRIVE_S0S1 << GPIO_PIN_CNF_DRIVE_Pos)
                       | ((uint32_t)GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos);
  
    while (1) {
        if ((millis() - ms) > 500) {
            ms = millis();
            pins_state = NRF_P1->OUT;
            NRF_P1->OUTSET = (~pins_state & (1UL << PIN));
            NRF_P1->OUTCLR = (pins_state & (1UL << PIN)); 
        }
        systick_evt();
    }
}
