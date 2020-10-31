#ifndef __HAL_UART_H
#define __HAL_UART_H

#include <stdint.h>
#include <stdbool.h>
#include "hal-gpio.h"

typedef enum {
    UART_0,
    UART_1,
    UART_2,
    UART_MAX,
} uart_t;

typedef enum {
    NONE,
    EVEN,
    ODD,
} uart_parity_t;

typedef uint8_t (*uart_tx_cb_t)(uart_t);
typedef void (*uart_rx_cb_t)(uart_t, uint8_t);

typedef struct {
    uint32_t wBaudRate;
    int8_t cDataBits;
    bool bParity;
    int8_t cStopBits;

    uart_tx_cb_t fnTxCb;
    uart_rx_cb_t fnRxCb;
} uart_cfg_t;

extern void hal_uart_init(uart_t tUart, gpio_t tTxPin, gpio_t tRxPin, const uart_cfg_t *c_pCfg);
extern bool hal_uart_tx(uart_t tUart, uint8_t chData);
extern bool hal_uart_rx(uart_t tUart, uint8_t *pchData);

#endif
