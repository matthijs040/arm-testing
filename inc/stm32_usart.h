#pragma once
#include <stdint.h>
#include "newlib_sys.h"
#include "stm32_usart_impl.h"

typedef enum {
    none = 0,
    odd = 1,
    even = 2,
} parity_t;
