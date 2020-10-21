#include "nrf.h"

#include <stdint.h>

#define SYSTICK_TICK_UNIT_NS            (50 * 1000)

uint64_t systick_cnt = 0;

void systick_evt(void)
{
    systick_cnt++;
}

uint32_t millis()
{
    return systick_cnt * SYSTICK_TICK_UNIT_NS / 1000000;
}

//P1.07

#define PIN         7
int main(void)
{
    uint32_t ms = millis();
    uint32_t pins_state;
	
    NRF_P1->PIN_CNF[PIN] = ((uint32_t)GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos)
                       | ((uint32_t)GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos)
                       | ((uint32_t)GPIO_PIN_CNF_PULL_Disabled << GPIO_PIN_CNF_PULL_Pos)
                       | ((uint32_t)GPIO_PIN_CNF_DRIVE_S0S1 << GPIO_PIN_CNF_DRIVE_Pos)
                       | ((uint32_t)GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos);

    pins_state = NRF_P1->OUT;
    NRF_P1->OUTSET = (~pins_state & (1UL << PIN));
    NRF_P1->OUTCLR = (pins_state & (1UL << PIN));
    
    while (1) {
        if ((millis() - ms) > 1000) {
            ms = millis();
            pins_state = NRF_P1->OUT;
            NRF_P1->OUTSET = (~pins_state & (1UL << PIN));
            NRF_P1->OUTCLR = (pins_state & (1UL << PIN)); 
        }
        systick_evt();
    }
}
