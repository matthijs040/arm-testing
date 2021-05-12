#include <stdio.h>

static const int uart_put(char c, FILE* f)
{ return 0; }

static const int uart_get(FILE* f)
{ return 0; }

static const int uart_flush(FILE* f)
{ return 0; }


FILE usart2_stdio = FDEV_SETUP_STREAM(uart_put, uart_get, uart_flush, _FDEV_SETUP_RW);
struct __file *const __iob[] = {
    &usart2_stdio,
    &usart2_stdio,
    &usart2_stdio
};

int main(void)
{  
    fputs("Hello world!", stdout);
    
    return 0;
}