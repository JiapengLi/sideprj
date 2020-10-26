#include "hal.h"
#include "hal-uart.h"

void system_init(void)
{
    uart_cfg_t tUartCfg;

    hal_clk_init();

    hal_gpio_init(LED1_PIN, GPIO_OUTPUT);
    hal_gpio_init(LED2_PIN, GPIO_OUTPUT);
    hal_gpio_init(LED3_PIN, GPIO_OUTPUT);
    hal_gpio_write(LED1_PIN, LED_OFF);
    hal_gpio_write(LED2_PIN, LED_OFF);
    hal_gpio_write(LED3_PIN, LED_OFF);

    hal_gpio_init(KEY1_PIN, GPIO_INPUT_PU);
    hal_gpio_init(KEY2_PIN, GPIO_INPUT_PU);

    tUartCfg.wBaudRate = 9600;
    tUartCfg.cDataBits = 8;
    tUartCfg.bParity = NONE;
    tUartCfg.cStopBits = 1;
    hal_uart_init(UART_0, P0_16, P0_15, &tUartCfg);

    breathled_init();
}

bool serial_in(uint8_t *pData)
{
    return hal_uart_rx(UART_0, pData);
}

bool serial_out(uint8_t pData)
{
    return hal_uart_tx(UART_0, pData);
}

uint32_t millis(void)
{
    return hal_systick_emu_millis();
}

/*-------------------------------------------------------------------------*/
// pwm module
typedef struct {
    uint32_t wArr;
    uint32_t wCnt;
    uint32_t wCmp;
    uint32_t wNextCmp;
} pwm_emu_t;

pwm_emu_t g_tPWMEmu;

void pwm_emu_init(uint32_t wArr, uint32_t wCmp)
{
    g_tPWMEmu.wCnt = 0;
    g_tPWMEmu.wArr = wArr;
    g_tPWMEmu.wCmp = wCmp;
    g_tPWMEmu.wNextCmp = wCmp;
    LED2_OFF();
}

void pwm_emu_update(uint32_t wCmp)
{
    g_tPWMEmu.wNextCmp = wCmp;
}

void pwm_emu_evt(void)
{
    g_tPWMEmu.wCnt++;
    if (g_tPWMEmu.wCnt > g_tPWMEmu.wArr) {
        g_tPWMEmu.wCnt = 0;

        g_tPWMEmu.wCmp = g_tPWMEmu.wNextCmp;

        if (g_tPWMEmu.wCmp != 0) {
            LED2_ON();
        } else {
            LED2_OFF();
        }
    }
    if (g_tPWMEmu.wCnt == g_tPWMEmu.wCmp) {
        LED2_OFF();
    }
}

/*-------------------------------------------------------------------------*/
// breath LED module
#define BLED_CYCLE                      (5 * 1000000 / SYSTICK_TIME_PER_TICK)
#define BLED_STEPS                      (1)

#define BLED_IDLE_DURATION              (100)
#define BLED_ON_DURATIOIN               (950)
#define BLED_OFF_DURATIOIN              (950)

typedef enum {
    BLED_STA_ON,
    BLED_STA_OFF,
    BLED_STA_IDLE,
} bled_sta_t;

typedef struct {
    bled_sta_t tSta;
    uint32_t wMs;
    uint32_t wTimeout;
    uint32_t wDutyCycle;
} bled_t;

static bled_t g_tBLED;

void breathled_init(void)
{
    pwm_emu_init(BLED_CYCLE, 0);

    g_tBLED.tSta = BLED_STA_ON;
    g_tBLED.wDutyCycle = 0;
    g_tBLED.wMs = 0;
    g_tBLED.wTimeout = 0;
}

void breathled(void)
{
    uint32_t wCurMs = millis();

    switch (g_tBLED.tSta) {
        case BLED_STA_ON:
            if ((wCurMs - g_tBLED.wTimeout) > 2) {
                g_tBLED.wTimeout = millis();
                g_tBLED.wDutyCycle += BLED_STEPS;
                pwm_emu_update(g_tBLED.wDutyCycle);
            }
            if ((wCurMs - g_tBLED.wMs) >= BLED_ON_DURATIOIN) {
                g_tBLED.wMs = millis();
                g_tBLED.tSta = BLED_STA_OFF;
            }
            break;
        case BLED_STA_OFF:
            if ((wCurMs - g_tBLED.wTimeout) > 2) {
                g_tBLED.wTimeout = millis();
                if (g_tBLED.wDutyCycle != 0) {
                    g_tBLED.wDutyCycle -= BLED_STEPS;
                }
                pwm_emu_update(g_tBLED.wDutyCycle);
            }
            if ((wCurMs - g_tBLED.wMs) >= BLED_OFF_DURATIOIN) {
                g_tBLED.wMs = millis();
                g_tBLED.tSta = BLED_STA_IDLE;
            }
            break;
        case BLED_STA_IDLE:
            if ((wCurMs - g_tBLED.wMs) >= BLED_IDLE_DURATION) {
                g_tBLED.wMs = millis();
                g_tBLED.tSta = BLED_STA_ON;
            }
            break;
    }

    /*  */
    pwm_emu_evt();

    /* systick emulator */
    hal_systick_emu_evt();
}
