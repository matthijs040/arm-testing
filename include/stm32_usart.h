#ifndef STM32_USART_H
#define STM32_USART_H

#include <stdint.h>

typedef enum {
    none = 0,
    odd = 1,
    even = 2,
} parity_t;

void usart_init(uint8_t usart, uint32_t baudrate, parity_t parity);

void usart_send(char* string);

void usart_recv();


#endif