// #include "inc/stm32f30x.h"
#include "inc/newlib_sys.h"


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// exit:
// void _exit(int status) { while(true); }

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
    
    fputs("Hello world!", stdout);
    
    return 0;
}