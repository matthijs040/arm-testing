#pragma once
#include <stdint.h>
#include "newlib_sys.h"
#include "stm32_usart_impl.h"

typedef enum {
    none = 0,
    odd = 1,
    even = 2,
} parity_t;

static devoptab_t usart_dev =  {
    .name = "usart_dev",
    .open_r = open_uart,
    .close_r = close_uart,
    .write_r = write_uart,
    .read_r = read_uart,
};