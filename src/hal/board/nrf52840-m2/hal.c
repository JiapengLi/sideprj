#include "hal.h"
#include "hal-uart.h"

void system_init(void)
{
    uart_cfg_t uart_cfg;
    
    hal_clk_init();
    
    hal_gpio_init(LED1_PIN, GPIO_OUTPUT);
    hal_gpio_init(LED2_PIN, GPIO_OUTPUT);
    hal_gpio_init(LED3_PIN, GPIO_OUTPUT);
    hal_gpio_write(LED1_PIN, LED_OFF);
    hal_gpio_write(LED2_PIN, LED_OFF);
    hal_gpio_write(LED3_PIN, LED_OFF);
    
    hal_gpio_init(KEY1_PIN, GPIO_INPUT_PU);
    hal_gpio_init(KEY2_PIN, GPIO_INPUT_PU);
    
    uart_cfg.baudrate = 9600;
    uart_cfg.data_bits = 8;
    uart_cfg.parity = NONE;
    uart_cfg.stop_bits = 1;
    hal_uart_init(UART_0, P0_16, P0_15, &uart_cfg);
    
    breathled_init();
}

bool serial_in(uint8_t *dt)
{
    return hal_uart_rx(UART_0, dt);
}

bool serial_out(uint8_t dt)
{
    return hal_uart_tx(UART_0, dt);
}

uint32_t millis(void)
{
    return hal_systick_emu_millis();
}

typedef enum {
    BLED_STA_ON,
    BLED_STA_OFF,
    BLED_STA_IDLE,
} bled_sta_t;

typedef struct {
    bled_sta_t sta;
    uint32_t ms;
    uint32_t thld;
    uint32_t cnt;
    uint8_t dir;
} bled_t;

bled_t bled;

#define BLED_PERIOD                     (40)
#define BLED_SPEED                      (2)


#define BLED_CYCLE                      (5 * 1000000 / SYSTICK_TIME_PER_TICK)

#define BLED_IDLE_DURATION              (100)
#define BLED_ON_DURATIOIN               (950)
#define BLED_OFF_DURATIOIN              (950)

void breathled_init(void)
{
    bled.sta = BLED_STA_ON;
    bled.ms = 0;
    bled.thld = 0;
    bled.cnt = 0;
    bled.dir = 0;
}

void breadthled_set_sta(bled_sta_t sta)
{
    switch (sta) {
    case BLED_STA_ON:
        bled.dir = 0;
        bled.cnt = 0;
        bled.thld = 0;
        LED2_OFF();
        break;
    case BLED_STA_OFF:
        bled.dir = 1;
        break;
    case BLED_STA_IDLE:
        bled.sta = BLED_STA_IDLE;
        LED2_OFF();
        break;
    }
    bled.sta = sta;
    bled.ms = millis();
}

void breathled_control(void)
{
    bled.cnt++;
    if (bled.cnt >= BLED_CYCLE) {
        bled.cnt = 0;
        if (bled.dir == 0) {
            bled.thld++;
        } else {
            if (bled.thld != 0) {
                bled.thld--;
            }
        }
        if (bled.thld != 0) {
            LED2_ON();
        } else {
            LED2_OFF();
        }
    } else if (bled.cnt == bled.thld) {
        LED2_OFF();
    }
}

void breathled(void)
{
    uint32_t curms = millis();
    
    switch (bled.sta) {
    case BLED_STA_ON:
        breathled_control();
        if ((curms - bled.ms) >= BLED_ON_DURATIOIN) {
            breadthled_set_sta(BLED_STA_OFF);
            //breadthled_set_sta(BLED_STA_IDLE);
        }
        break;
    case BLED_STA_OFF:
        breathled_control();
        if ((curms - bled.ms) >= BLED_OFF_DURATIOIN) {
            breadthled_set_sta(BLED_STA_IDLE);
        }
        break;
    case BLED_STA_IDLE:
        if ((curms - bled.ms) >= BLED_IDLE_DURATION) {
            //breadthled_set_sta(BLED_STA_OFF);
            breadthled_set_sta(BLED_STA_ON);
        }
        break;
    }
}
