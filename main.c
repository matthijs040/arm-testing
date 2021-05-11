#include "stm32f30x.h"


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// static const int uart_stdout(const char c, FILE* stream)
// {
//     if(c == '\n')
//         uart_putc('\r');
//     uart_putc(c);
//     return 0;
// }
// 
// static const int uart_stdin(FILE* stream) 
// {
//     return (uint8_t)uart_getc();   
// }


int main(void)
{
    // stdin = uart_stdin; 
    // stdout = stderr = uart_stdout;
    // puts("Hello world!");
    USART_InitTypeDef usart_initialization;
    usart_initialization.USART_BaudRate             = 115200;
    usart_initialization.USART_HardwareFlowControl  = USART_HardwareFlowControl_None;
    usart_initialization.USART_Mode                 = USART_Mode_Tx;
    usart_initialization.USART_Parity               = USART_Parity_No;
    usart_initialization.USART_StopBits             = USART_StopBits_1;
    usart_initialization.USART_WordLength           = USART_WordLength_8b;

    USART_Init(USART2, &usart_initialization);
    usart_initialization.USART_BaudRate++;

    while(true);
}