#include "hal.h"
#include "hal-uart.h"

typedef struct {
    bool tx;
} _uart_t;

_uart_t uart_tab[UART_MAX];

static uint32_t get_br(uint32_t br)
{
    switch (br) {
    case 1200:
        return UART_BAUDRATE_BAUDRATE_Baud1200;
    case 2400:
        return UART_BAUDRATE_BAUDRATE_Baud2400;
    case 4800:
        return UART_BAUDRATE_BAUDRATE_Baud4800;
    case 9600:
        return UART_BAUDRATE_BAUDRATE_Baud9600;
    case 14400:
        return UART_BAUDRATE_BAUDRATE_Baud14400;
    case 19200:
        return UART_BAUDRATE_BAUDRATE_Baud19200;
    case 28800:
        return UART_BAUDRATE_BAUDRATE_Baud28800;
    case 31250:
        return UART_BAUDRATE_BAUDRATE_Baud31250;
    case 38400:
        return UART_BAUDRATE_BAUDRATE_Baud38400;    
    case 56000:
        return UART_BAUDRATE_BAUDRATE_Baud56000;
    case 76800:
        return UART_BAUDRATE_BAUDRATE_Baud76800;
    case 115200:
        return UART_BAUDRATE_BAUDRATE_Baud115200;    
    case 230400:
        return UART_BAUDRATE_BAUDRATE_Baud230400;
    case 250000:
        return UART_BAUDRATE_BAUDRATE_Baud250000;
    case 460800:
        return UART_BAUDRATE_BAUDRATE_Baud460800;     
    case 921600:
        return UART_BAUDRATE_BAUDRATE_Baud921600;  
    case 1000000:
        return UART_BAUDRATE_BAUDRATE_Baud1M;  
    default:
        return (uint32_t)(((uint64_t)br << 32) / 16000000);    
    }
}





void hal_uart_init(uart_t uart, gpio_t txpin, gpio_t rxpin, const uart_cfg_t *cfg)
{
    uint32_t config;
    switch (uart) {
    case UART_0:
        config = 0;
        if (cfg->stop_bits == 2) {
            config |= UART_CONFIG_STOP_Two << UART_CONFIG_STOP_Pos;
        } else {
            config |= UART_CONFIG_STOP_One << UART_CONFIG_STOP_Pos;
        }
        if (cfg->parity == NONE) {
            config |= UART_CONFIG_PARITY_Excluded << UART_CONFIG_PARITY_Pos;
        } else {
            config |= UART_CONFIG_STOP_One << UART_CONFIG_STOP_Pos;
        }
    
        uart_tab[UART_0].tx = false;
        hal_gpio_init(txpin, GPIO_OUTPUT_PP);
        
        NRF_UART0->ENABLE = UART_ENABLE_ENABLE_Disabled;
        NRF_UART0->CONFIG = config;
        NRF_UART0->BAUDRATE = get_br(cfg->baudrate);
        
        NRF_UART0->PSEL.TXD = txpin;
        NRF_UART0->PSEL.RXD = rxpin;
        
        NRF_UART0->ENABLE = UART_ENABLE_ENABLE_Enabled;
        NRF_UART0->TASKS_STARTTX = UART_TASKS_STARTTX_TASKS_STARTTX_Trigger;
        NRF_UART0->TASKS_STARTRX = UART_TASKS_STARTRX_TASKS_STARTRX_Trigger;
        break;
    case UART_1:
        
        break;
    case UART_2:
        
        break;
    }

}

bool hal_uart_is_tx_empty(uart_t uart)
{
    switch (uart) {
    case UART_0:
        return (NRF_UART0->EVENTS_TXDRDY != 0);
    case UART_1:
        
        break;
    case UART_2:
        
        break;
    }
    return false;
}

bool hal_uart_tx(uart_t uart, uint8_t dt)
{
    switch (uart) {
    case UART_0:
        if ((NRF_UART0->EVENTS_TXDRDY != 0) || (!uart_tab[uart].tx)) {
            NRF_UART0->EVENTS_TXDRDY = 0;
            uart_tab[uart].tx = true;
            NRF_UART0->TXD = dt;
            return true;
        }
    case UART_1:
        
        break;
    case UART_2:
        
        break;
    }
    return false;
}


bool hal_uart_rx(uart_t uart, uint8_t *dt)
{
    switch (uart) {
    case UART_0:
        if (NRF_UART0->EVENTS_RXDRDY != 0) {
            NRF_UART0->EVENTS_RXDRDY = 0;
            *dt = NRF_UART0->RXD;
            return true;
        }
    case UART_1:
        
        break;
    case UART_2:
        
        break;
    }
    return false;
}

