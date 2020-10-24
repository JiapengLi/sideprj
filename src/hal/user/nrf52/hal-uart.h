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

typedef enum{
	NONE,
  	EVEN,
	ODD,
}uart_parity_t;

typedef uint8_t (*uart_tx_cb_t) (uart_t);
typedef void (*uart_rx_cb_t) (uart_t, uint8_t);

typedef struct {
    uint32_t baudrate;
    int8_t data_bits;
    bool parity;
    int8_t stop_bits;
    
    uart_tx_cb_t txcb;
    uart_rx_cb_t rxcb;
} uart_cfg_t;

void hal_uart_init(uart_t uart, gpio_t txpin, gpio_t rxpin, const uart_cfg_t *cfg);
bool hal_uart_tx(uart_t uart, uint8_t dt);
bool hal_uart_rx(uart_t uart, uint8_t *dt);

#endif
